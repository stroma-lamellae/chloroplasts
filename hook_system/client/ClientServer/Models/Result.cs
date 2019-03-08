using System;
using System.Collections.Generic;

namespace ClientServer.Models
{
    public class Result
    {
        public long ResultId { get; set; }
        public DateTime CompletedDate { get; set; }
        public long PackageId { get; set; }
        
        public virtual Package Package { get; set; }
        public virtual  ICollection<Match> Matches { get; set; }
    }
}