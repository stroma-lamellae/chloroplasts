using System.Collections.Generic;
using Newtonsoft.Json;

namespace ClientServer.Models
{
    public class Course
    {
        public long CourseId { get; set; }
        public string UserId { get; set; }
        public int Year { get; set; }
        public int Semester { get; set; }
        public string ProgramCode { get; set; }
        public string CourseCode { get; set; }
        
        // [JsonIgnore]
        public virtual List<Assignment> Assignments { get; set; }
    }
}