using System.Xml.Serialization;
using System.Threading.Tasks;
using System.IO;
using System;
using System.Text;

using ClientServer.Models;

namespace ClientServer.Services
{
    public interface IXMLService
    {
        Result ParseXMLFile(string data);
    }

    public class XMLService: IXMLService
    {
        public Result ParseXMLFile(string data)
        {
            Console.WriteLine(data);
            Console.WriteLine("Hello There");
            XmlSerializer ser = new XmlSerializer(typeof(Results));
            Results results = ((Results)ser.Deserialize(new MemoryStream(Encoding.UTF8.GetBytes(data ?? ""))));
            Result result = new Result();
            result.CompletedDate = DateTime.UtcNow;
            if (results.matches != null) {
                foreach (var match in results.matches) {
                    Match modelMatch = new Match();

                    Line line1 = new Line();
                    Line line2 = new Line();
                    XMLSubmission sub1 = match.submissions[0];
                    XMLSubmission sub2 = match.submissions[1];
                    line1.SubmissionId = DeHash(sub1.hash);
                    line2.SubmissionId = DeHash(sub2.hash);

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
        private int DeHash(string hash)
        {
            return 1;
        }
    }


    public class XMLSubmission
    {
        public string hash { get; set; }
        public string file { get; set; }
        public int line_start { get; set; }
        public int line_finish { get; set; }
    }

    public class XMLMatch
    {
        public int number { get; set; }
        public XMLSubmission[] submissions { get; set; }
    }

    public class Results
    {
        public XMLMatch[] matches { get; set; }
    }
}