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
        Task<ResultsResponse> RequestResults(long JobId);
    }

    public class ProcessingService : IProcessingService
    {
        private readonly IHttpClientFactory _clientFactory;
        private readonly string ServerAddress = "http://localhost:3000";

        public ProcessingService(IHttpClientFactory clientFactory)
        {
            _clientFactory = clientFactory;
        }

        public async Task<ResultsResponse> InitiateUpload(Package package)
        {
            var uploadRequest = CreateUploadRequest(package);

            var client = _clientFactory.CreateClient();

            // Send to processing server
            var content = new StringContent(JsonConvert.SerializeObject(package), Encoding.UTF8, "application/json");
            var requestAddress = ServerAddress + "/submit";
            var response = await client.PostAsync(requestAddress, content);

            // Handle Response
            var responseText = await response.Content.ReadAsStringAsync();
            var resultsResponse = JsonConvert.DeserializeObject<ResultsResponse>(responseText);
            
            return resultsResponse;
        }

        public UploadRequest CreateUploadRequest(Package package) 
        {
            // TODO: Scrub package to create tarball
            // TODO: Get real data
            return new UploadRequest { 
                UserId = 123456, // TODO: Should come from authservice
                Email = "jb15iq@brocku.ca", // TODO: Should come from user id
                AuthToken = "Hahhahahahahaha We don't have this yet :)",
<<<<<<< HEAD
                FileName = "FakeData.tar.gz"
=======
                Tarball = "Some data :+1:"
>>>>>>> 75fd07c... Added processing service to communicate with Processing Server. Rewrote PackageController to make use of this.
            };
        }

        public async Task<ResultsResponse> RequestResults(long JobId)
        {
            // TODO: Get the resultsRequest to be real
            var resultsRequest = new ResultsRequest {
                UserId = 123456, // TODO: Should come from authservice
                JobId = JobId,
                AuthToken = "Hahhahahahahahah This isn't the same authtoken. Oh well."
            }; 

            var client = _clientFactory.CreateClient();

            // Send to processing server
            var content = new StringContent(JsonConvert.SerializeObject(resultsRequest), Encoding.UTF8, "application/json");
            var requestAddress = ServerAddress + "/request";
            var response = await client.PostAsync(requestAddress, content);

            // Handle Response
            var responseText = await response.Content.ReadAsStringAsync();
<<<<<<< HEAD
            var resultsResponse = JsonConvert.DeserializeObject<ResultsResponse>(responseText);
=======
            var resultsResponse = (ResultsResponse) (JsonConvert.DeserializeObject(responseText));
>>>>>>> 75fd07c... Added processing service to communicate with Processing Server. Rewrote PackageController to make use of this.

            return resultsResponse;
        }
    }

    public class UploadRequest
    {
        public long UserId { get; set; }
        public string Email { get; set; }
        public string AuthToken { get; set; }
<<<<<<< HEAD
        public string FileName { get; set; } // TODO: Make this be a file
=======
        public string Tarball { get; set; } // TODO: Make this be a file
>>>>>>> 75fd07c... Added processing service to communicate with Processing Server. Rewrote PackageController to make use of this.
    }

    public class ResultsRequest
    {
        public long UserId { get; set; }
        public long JobId { get; set; }
        public string AuthToken { get; set; }
    }

    public class ResultsResponse
    {
        public string Status { get; set; }
        public long JobId { get; set; }
<<<<<<< HEAD
        public string EstimatedWaitTime { get; set; }
=======
        public DateTime? EstimatedWaitTime { get; set; }
>>>>>>> 75fd07c... Added processing service to communicate with Processing Server. Rewrote PackageController to make use of this.
        public string Results { get; set; } // TODO: Make this be a file
    }
}