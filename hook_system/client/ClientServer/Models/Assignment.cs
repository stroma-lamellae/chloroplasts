using System.Collections.Generic;

namespace ClientServer.Models
{
    public class Assignment
    {
        public long AssignmentId { get; set; }
        public string Name { get; set; }
        public string Locaiton { get; set; }
        
        public long CourseId { get; set; }
        public Course Course { get; set; }

        public List<Submission> Submissions { get; set; }
    }
}