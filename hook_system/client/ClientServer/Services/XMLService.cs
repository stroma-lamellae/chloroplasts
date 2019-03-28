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
            XmlSerializer ser = new XmlSerializer(typeof(results));
            results results = ((results)ser.Deserialize(new MemoryStream(Encoding.UTF8.GetBytes(data ?? ""))));
            Result result = new Result();
            result.Matches = new List<Match>();
            result.CompletedDate = DateTime.UtcNow;
            if (results.matches != null) {
                foreach (var match in results.matches) {
                    Match modelMatch = new Match();
                    modelMatch.Lines = new List<Line>();

                    Line line1 = new Line();
                    Line line2 = new Line();
                    submission sub1 = match.submissions[0];
                    submission sub2 = match.submissions[1];
                    line1.SubmissionId = await DeHash(sub1.hash);
                    line2.SubmissionId = await DeHash(sub2.hash);

                    line1.LineStart = sub1.line_start;
                    line2.LineStart = sub2.line_start;

                    line1.LineEnd = sub1.line_finish;
                    line2.LineEnd = sub2.line_finish;

                    line1.FilePath = sub1.file;
                    line2.FilePath = sub2.file;

                    modelMatch.Lines.Add(line1);
                    modelMatch.Lines.Add(line2);
                    
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
            var something = await _context.Submission
                .Where(s => s.StudentFirstname == hashMapping.Firstname)
                .Where(s => s.StudentLastname == hashMapping.Lastname)
                .Where(s => s.StudentNumber == hashMapping.StudentNumber)
                .FirstAsync();
            return something.SubmissionId;
        }
    }


    public class submission
    {
        public string hash { get; set; }
        public string file { get; set; }
        public int line_start { get; set; }
        public int line_finish { get; set; }
    }

    public class match
    {
        public int number { get; set; }
        public submission[] submissions { get; set; }
    }

    public class results
    {
        public match[] matches { get; set; }
    }
}