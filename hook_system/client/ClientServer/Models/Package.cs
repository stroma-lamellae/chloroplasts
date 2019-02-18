<<<<<<< HEAD
using System;
=======
>>>>>>> 991fe02... Base structure for the Client Server. Some models, and an api to go along with those models.
using System.Collections.Generic;

namespace ClientServer.Models
{
    public class Package
    {
        public long PackageId { get; set; }
<<<<<<< HEAD
        public long AssignmentId { get; set; }
        public long ResultId { get; set; }
        public DateTime EstimatedCompletion { get; set; }
       
        public virtual Assignment Assignment { get; set; }
        public virtual Result Result { get; set; }
        public virtual ICollection<Assignment> PreviousAssignments { get; set; }
=======
        public long CurrentAssignmentId { get; set; }
        public Assignment CurrentAssignment { get; set; }
        public List<Assignment> PreviousAssignments { get; set; }
>>>>>>> 991fe02... Base structure for the Client Server. Some models, and an api to go along with those models.
    }
}