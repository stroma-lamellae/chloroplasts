using System.Collections.Generic;

namespace ClientServer.Models
{
    public class Course
    {
        public long CourseId { get; set; }
        public long OwnerId { get; set; }
        public int Year { get; set; }
        public int Semester { get; set; }
        public string Name { get; set; }

        public List<Assignment> Assignments { get; set; }
    }
}