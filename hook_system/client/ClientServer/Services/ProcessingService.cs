using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Microsoft.AspNetCore.Http;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Net;
using System.Security.Claims;
using Microsoft.AspNetCore.Identity;

using ClientServer.Models;

/*
This deals with all of the communication between the Client Server and the Processing Server
 */

namespace ClientServer.Services
{
    public interface IProcessingService
    {
        Task<UploadResponse> InitiateUpload(Package package, bool scrub = true);
        Task<ResultsResponse> RequestResults(Package package);
    }

    public class ProcessingService : IProcessingService
    {
        private readonly IHttpClientFactory _clientFactory;
        private readonly IXMLService _xmlService;
        private readonly IScrubbingService _scrubbingService;
        private readonly IFileService _fileService;
        private readonly string _tempTestDirectory = "test";
        private readonly string _institutionId;
        private readonly IHttpContextAccessor _httpContextAccessor;
        private readonly UserManager<AppUser> _userManager;

        public ProcessingService(IHttpClientFactory clientFactory, IXMLService xmlService, IScrubbingService scrubbingService, IConfiguration configuration, 
                                 IFileService fileService, IHttpContextAccessor httpContextAccessor, UserManager<AppUser> userManager)
        {
            _clientFactory = clientFactory;
            _xmlService = xmlService;
            _scrubbingService = scrubbingService;
            _fileService = fileService;
            _institutionId = configuration.GetSection("ProcessingConfigurations")["InstitutionId"];
            _httpContextAccessor = httpContextAccessor;
            _userManager = userManager;
        }

        public async Task<UploadResponse> InitiateUpload(Package package, bool scrub = true)
        {
            string filename = "";
            if (scrub) {
                filename = _scrubbingService.ScrubPackage(package);
            } else {
                // Don't scrub files, just compress and send
                _fileService.EmptyDirectory(_tempTestDirectory);
                var currAssignmentPath = Path.Combine(_tempTestDirectory, "CurrentYear");
                _fileService.CopyAssignment(package.Assignment, currAssignmentPath, true);

                filename = Path.Combine(Path.GetTempPath(), Path.GetTempFileName() + ".tar.gz");
                _fileService.CompressFolder(_tempTestDirectory, filename);
            }

            var uploadRequest = await CreateUploadRequest(filename);

            var client = _clientFactory.CreateClient("processing");

            var requestAddress = $"api/submit?userId={uploadRequest.InstitutionId}&email={uploadRequest.Email}";

            // Create the multipart form portion of the request
            var formDataContent = new MultipartFormDataContent();

            // Create a form part for the file
            var fileContent = new StreamContent(File.OpenRead(filename))
            {
                Headers = 
                {
                    ContentLength = new FileInfo(filename).Length,
                    ContentType = new MediaTypeHeaderValue("application/zip")
                }
            };

            // Add the file form part to our form data
            formDataContent.Add(fileContent, "data", uploadRequest.FileName);

            // Send to the processing server
            var response = await client.PostAsync(requestAddress, formDataContent);
            
            // Handle Response
            var responseText = await response.Content.ReadAsStringAsync();
            var resultsResponse = JsonConvert.DeserializeObject<UploadResponse>(responseText);
            resultsResponse.StatusCode = response.StatusCode;
            if (response.StatusCode == HttpStatusCode.OK) {
                resultsResponse.EstimatedCompletionTime = DateTime.Parse(resultsResponse.EstimatedCompletion);
            }
            return resultsResponse; 
        }

        public async Task<UploadRequest> CreateUploadRequest(string filename) 
        {
            var email = await _userManager.FindByIdAsync(_httpContextAccessor.HttpContext.User.FindFirst("userId").Value);

            return new UploadRequest { 
                InstitutionId = _institutionId, 
                Email = email.ToString(),
                FileName = filename
            };
        }

        public async Task<ResultsResponse> RequestResults(Package package)
        {
            var resultsRequest = new ResultsRequest {
                InstitutionId = _institutionId, 
                JobId = package.JobId
            }; 

            var client = _clientFactory.CreateClient("processing");

            // Send to processing server
            var content = new StringContent(JsonConvert.SerializeObject(resultsRequest), Encoding.UTF8, "application/json");
            var requestAddress = $"api/results?userId={resultsRequest.InstitutionId}&jobId={resultsRequest.JobId}";
            var response = await client.PostAsync(requestAddress, content);

            // Handle Response
            var responseText = await response.Content.ReadAsStringAsync();
            var resultsResponse = JsonConvert.DeserializeObject<ResultsResponse>(responseText);
            resultsResponse.StatusCode = response.StatusCode;
            // If we got results returned
            if (resultsResponse.Status.Equals("Ok")) {
                resultsResponse.Result = await _xmlService.ParseXMLFile(package, resultsResponse.Results);
            } else {
                if (resultsResponse.Wait != "")
                {
                    resultsResponse.EstimatedCompletion = DateTime.Parse(resultsResponse.Wait);
                }
            }
            return resultsResponse;
        }
    }

    public class UploadRequest
    {
        public string InstitutionId { get; set; }
        public string Email { get; set; }
        public string FileName { get; set; } 
    }

    public class UploadResponse
    {
        public string JobId { get; set; }
        public string EstimatedCompletion { get; set; }
        public DateTime EstimatedCompletionTime { get; set; }
        public string Status { get; set; }
        public HttpStatusCode StatusCode { get; set; }
    }

    public class ResultsRequest
    {
        public string InstitutionId { get; set; }
        public string JobId { get; set; }
    }

    public class ResultsResponse
    {
        public string Status { get; set; }
        public string Wait { get; set; }
        public string Results { get; set; } 

        public Result Result { get; set; }
        public HttpStatusCode StatusCode { get; set; }
        public DateTime EstimatedCompletion { get; set; }
    }
}