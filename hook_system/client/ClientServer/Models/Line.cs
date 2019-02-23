namespace ClientServer.Models
{
    public class Line
    {
        public long LineId { get; set; }
        public long MatchId { get; set; }
        public long SubmissionId { get; set; }
        public int LineStart { get; set; }
        public int LineEnd { get; set; }
        public string FilePath { get; set; }
        
        public virtual Match Match { get; set; }
        public virtual Submission Submission { get; set; }
    }
}