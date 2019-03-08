namespace ClientServer.Models
{
    public class PreviousAssignment
    {
        public long PreviousAssignmentId { get; set; }
        public long AssignmentId { get; set; }
        public long PackageId { get; set; }
        
        public virtual Assignment Assignment { get; set; }
        public virtual Package Package { get; set; }
    }
}