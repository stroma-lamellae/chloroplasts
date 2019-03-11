using System.Collections.Generic;

namespace ClientServer.Models
{
    public class StudentHashMapping
    {
        public long StudentHashMappingId{get;set;}
        public string Firstname { get; set; }
        public string Lastname { get; set; }
        public string StudentNumber { get; set; }
        public string Hash_Firstname { get; set; }
        public string Hash_Lastname { get; set; }
        public string Hash_StudentNumber { get; set; }
    }
}