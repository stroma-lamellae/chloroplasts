using Microsoft.EntityFrameworkCore;
using System.Xml.Serialization;
using System.Threading.Tasks;
using System.IO;
using System;
using System.Linq;
using System.Text;
using System.Collections.Generic;

using ClientServer.Models;

namespace ClientServer.Services
{
    public interface IXMLService
    {
        Task<Result> ParseXMLFile(string data);
    }

    public class XMLService: IXMLService
    {
        private readonly ClientServerContext _context;

        public XMLService(ClientServerContext context)
        {
            _context = context;
        }
        public async Task<Result> ParseXMLFile(string data)
        {
            XmlSerializer ser = new XmlSerializer(typeof(Results));
            Results results = ((Results)ser.Deserialize(new MemoryStream(Encoding.UTF8.GetBytes(data ?? ""))));
            Result result = new Result();
            result.Matches = new List<Match>();
            result.CompletedDate = DateTime.UtcNow;
            // Check if the results are available yet
            if (results.Matches == null || results.Matches.Length == 0) {
                return null;
            }
            if (results.Matches != null) {
                foreach (var match in results.Matches) {
                    Match modelMatch = new Match();
                    modelMatch.Lines = new List<Line>();
                    foreach (var sub in match.Submissions) {
                        var line = new Line();
                        line.SubmissionId = await DeHash(sub.Hash);
                        line.LineStart = sub.LineStart;
                        line.LineEnd = sub.LineFinish;
                        line.FilePath = sub.File;
                        modelMatch.Lines.Add(line);
                    }
                    
                    result.Matches.Add(modelMatch);
                }
            }
            return result;
        }

        // Looks up the hash, and returns the submission id
        private async Task<long> DeHash(string hash)
        {
            var hashMapping = await _context.StudentHashMapping
                .Where(s => s.Hash_StudentNumber == hash)
                .FirstAsync();
            var submission = await _context.Submission
                .Where(s => s.StudentFirstname == hashMapping.Firstname)
                .Where(s => s.StudentLastname == hashMapping.Lastname)
                .Where(s => s.StudentNumber == hashMapping.StudentNumber)
                .FirstAsync();
            return submission.SubmissionId;
        }
    }

    [XmlRoot("submission")]
    public class XMLSubmission
    {
        [XmlElement(ElementName = "hash")]
        public string Hash { get; set; }

        [XmlElement(ElementName = "file")]
        public string File { get; set; }

        [XmlElement(ElementName = "line_start")]
        public int LineStart { get; set; }

        [XmlElement(ElementName = "line_finish")]
        public int LineFinish { get; set; }
    }

    [XmlRoot("match")]
    public class XMLMatch
    {
        [XmlElement(ElementName = "number")]
        public int Number { get; set; }

        [XmlArray("submissions")]
        [XmlArrayItem("submission")]
        public XMLSubmission[] Submissions { get; set; }
    }

    [XmlRoot("results")]
    public class Results
    {
        [XmlArray("matches")]
        [XmlArrayItem("match")]
        public XMLMatch[] Matches { get; set; }
    }
}
