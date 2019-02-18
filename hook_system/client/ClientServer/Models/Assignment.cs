using System;
using System.Collections.Generic;

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
        public Course Course { get; set; }
        public ICollection<Submission> Submissions { get; set; }
    }
}