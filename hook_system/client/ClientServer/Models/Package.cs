using System;
using System;
using System.Collections.Generic;

namespace ClientServer.Models
{
    public class Package
    {
        public long PackageId { get; set; }
        public long AssignmentId { get; set; }
        public long JobId { get; set; }
        public DateTime EstimatedCompletion { get; set; }
        public virtual Assignment Assignment { get; set; }
        public virtual Result Result { get; set; }
        public virtual ICollection<PreviousAssignment> PreviousAssignments { get; set; }
    }
}