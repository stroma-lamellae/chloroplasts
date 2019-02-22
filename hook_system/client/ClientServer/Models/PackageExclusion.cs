namespace ClientServer.Models
{
    public class PackageExclusion
    {
        public long PackageExclusionId { get; set; }
        public long ExclusionId { get; set; }
        public long PackageId { get; set; }
        
        public virtual Exclusion Exclusion { get; set; }
        public virtual Package Package { get; set; }
    }
}