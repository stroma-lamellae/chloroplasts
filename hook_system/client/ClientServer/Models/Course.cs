using System.Collections.Generic;

namespace ClientServer.Models
{
    public class Course
    {
        public long CourseId { get; set; }
        public long UserId { get; set; }
        public int Year { get; set; }
        public int Semester { get; set; }
        public string ProgramCode { get; set; }
        public string CourseCode { get; set; }

        public virtual List<Assignment> Assignments { get; set; }
    }
}