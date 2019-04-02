using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Net.Http;
using System.Net.Http.Headers;

using ClientServer.Models;

/*
This deals with all of the communication between the Client Server and the Processing Server
 */

namespace ClientServer.Services
{
    public interface IProcessingService
    {
        Task<ResultsResponse> InitiateUpload(Package package);
        Task<ResultsResponse> RequestResults(string jobId);
    }

    public class ProcessingService : IProcessingService
    {
        private readonly IHttpClientFactory _clientFactory;
        private readonly IXMLService _xmlService;
        private readonly IScrubbingService _scrubbingService;

        public ProcessingService(IHttpClientFactory clientFactory, IXMLService xmlService, IScrubbingService scrubbingService)
        {
            _clientFactory = clientFactory;
            _xmlService = xmlService;
            _scrubbingService = scrubbingService;
        }

        public async Task<ResultsResponse> InitiateUpload(Package package)
        {
            var filename = _scrubbingService.ScrubPackage(package);

            var uploadRequest = CreateUploadRequest(package, filename);

            var client = _clientFactory.CreateClient("processing");

            var requestAddress = "api/submit?userId=" + uploadRequest.UserId + "&email=" + uploadRequest.Email;

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
            var responseText = await response.Content.ReadAsStringAsync();

            var resultsResponse = JsonConvert.DeserializeObject<ResultsResponse>(responseText);
            
            return resultsResponse;
        }

        public UploadRequest CreateUploadRequest(Package package, string filename) 
        {
            // TODO: Scrub package to create tarball
            // TODO: Get real data
            return new UploadRequest { 
                UserId = 123456, // TODO: Should come from authservice
                Email = "jb15iq@brocku.ca", // TODO: Should come from user id
                FileName = filename
            };
        }

        public async Task<ResultsResponse> RequestResults(string jobId)
        {
            // TODO: Get the resultsRequest to be real
            var resultsRequest = new ResultsRequest {
                UserId = 123456, // TODO: Should come from authservice
                JobId = jobId
            }; 

            var client = _clientFactory.CreateClient("processing");

            // Send to processing server
            var content = new StringContent(JsonConvert.SerializeObject(resultsRequest), Encoding.UTF8, "application/json");
            var requestAddress = "api/results?userId=" + resultsRequest.UserId + "&jobId=" + resultsRequest.JobId;
            var response = await client.PostAsync(requestAddress, content);

            // Handle Response
            var responseText = await response.Content.ReadAsStringAsync();
            var resultsResponse = JsonConvert.DeserializeObject<ResultsResponse>(responseText);

            var result = await _xmlService.ParseXMLFile(resultsResponse.Results);
            resultsResponse.Result = result;
            return resultsResponse;
        }
    }

    public class UploadRequest
    {
        public long UserId { get; set; }
        public string Email { get; set; }
        public string FileName { get; set; } 
    }

    public class ResultsRequest
    {
        public long UserId { get; set; }
        public string JobId { get; set; }
    }

    public class ResultsResponse
    {
        public string Status { get; set; }
        public string JobId { get; set; }
        public DateTime EstimatedCompletion { get; set; }
        public string Results { get; set; } 

        public Result Result { get; set; }
    }
}