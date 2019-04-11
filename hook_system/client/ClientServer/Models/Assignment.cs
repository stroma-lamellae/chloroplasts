using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace ClientServer.Models
{
    public class Assignment
    {
        public long AssignmentId { get; set; }
        public string Name { get; set; }
        public long CourseId { get; set; }
        public DateTime OpenDate { get; set; }
        public DateTime CloseDate { get; set; }
        public bool Status { get; set; }
        
        public virtual Course Course { get; set; }
        public virtual ICollection<Submission> Submissions { get; set; }
    }
}