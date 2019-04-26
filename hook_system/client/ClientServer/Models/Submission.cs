using Microsoft.AspNetCore.Http;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using Newtonsoft.Json;

namespace ClientServer.Models
{
    public class Submission
    {
        public long SubmissionId { get; set; }
        
        public long   AssignmentId { get; set; }
        public string FilePath { get; set; }
        public string StudentNumber { get; set; }
        public string StudentFirstname { get; set; }
        public string StudentLastname { get; set; }
        public long   StudentId { get; set; }
        
        public Assignment Assignment { get; set; }

        [NotMapped]
        public List<IFormFile> Files { get; set; }
    }
}