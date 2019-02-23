using System.Collections.Generic;

namespace ClientServer.Models
{
    public class Match
    {
        public long MatchId { get; set; }
        public long ResultId { get; set; }
        
        public virtual ICollection<Line> Lines { get; set; }
    }
}