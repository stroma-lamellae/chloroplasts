namespace ClientServer.Models
{
    public class Submission
    {
        public long SubmissionId { get; set; }
        
        public long AssignmentId { get; set; }
        public Assignment Assignment { get; set; }
    }
}