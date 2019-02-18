using System.Collections.Generic;

namespace ClientServer.Models
{
    public class Package
    {
        public long PackageId { get; set; }
        public long CurrentAssignmentId { get; set; }
        public Assignment CurrentAssignment { get; set; }
        public List<Assignment> PreviousAssignments { get; set; }
    }
}