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
        Task<Result> ParseXMLFile(Package package, string data);
    }

    public class XMLService: IXMLService
    {
        private readonly ClientServerContext _context;

        public XMLService(ClientServerContext context)
        {
            _context = context;
        }
        public async Task<Result> ParseXMLFile(Package package, string data)
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
            // Sort the submissions within each match
            foreach (var match in results.Matches) {
                Array.Sort(match.Submissions, (a, b) => {
                    var val = String.Compare(a.Hash, b.Hash);
                    if (val != 0) return val;
                    return String.Compare(a.File, b.File);
                });
            }
            // Sort the matches based on the following scheme:
            //  Sort by the number of submissions in a match
            //  Then sort by the names of who owns each of the submissions
            //  Then sort by the names of the file for each submission
            //  Then sort by line start
            //  Then sort by line end
            Array.Sort(results.Matches, (x, y) => {
                var diff = y.Submissions.Count() - x.Submissions.Count();
                if (diff != 0) return diff;

                for (int i = 0; i < x.Submissions.Count(); i++) {
                    var val = String.Compare(x.Submissions[i].Hash, y.Submissions[i].Hash);
                    if (val != 0) return val;
                }
                
                for (int i = 0; i < x.Submissions.Count(); i++) {
                    var val = String.Compare(x.Submissions[i].File, y.Submissions[i].File);
                    if (val != 0) return val;
                }

                diff = x.Submissions[0].LineStart - y.Submissions[0].LineStart;
                if (diff != 0) return diff;
                return x.Submissions[0].LineFinish - y.Submissions[0].LineFinish;
            });

            // Combine similar matches
            List<XMLMatch> matches = new List<XMLMatch>();
            matches.Add(results.Matches[0]);
            for (int i = 1; i < results.Matches.Count(); i++) {
                // Check if this match could be combined with the previous match
                // Needs to have the same submissions, but different line starts and line ends
                var match = results.Matches[i];
                var lastMatch = matches.Last();
                if (match.Submissions.Count() != lastMatch.Submissions.Count()) {
                    matches.Add(match);
                    continue;
                }
                bool keepGoing = true;
                for (int j = 0; j < match.Submissions.Count(); j++) {
                    if (!match.Submissions[j].Hash.Equals(lastMatch.Submissions[j].Hash)) {
                        keepGoing = false;
                        break;
                    }
                    if (!match.Submissions[j].File.Equals(lastMatch.Submissions[j].File)) {
                        keepGoing = false;
                        break;
                    }
                }
                if (!keepGoing) {
                    matches.Add(match);
                    continue;
                }
                // By now, the hashes and files match for each submission within the matches
                // Now, check if we can combine the line start and line finish
                // We can combine them in four cases: (If all submission follow the same pattern)
                // 1.   MATCH1:  -----
                //      MATCH2:  ~---~ 
                //      sol'n: don't add match 2
                //
                // 2.   MATCH1:  ~---~
                //      MATCH2:  -----
                //      sol'n: remove match 1 and add match 2
                //
                // 3.   MATCH1:  -----
                //      MATCH2:  ~~~-----
                //      sol'n: extend match 1
                //
                // 4.   MATCH1:  ~~~-----
                //      MATCH2:  -----
                //      sol'n: extend match 1

                // Determine pattern first, then take action
                int pattern = -1;
                bool shouldAggregate = true;
                for (int j = 0; j < match.Submissions.Count(); j++) {
                    int thisPattern = -1;

                    int lineStartDiff = lastMatch.Submissions[j].LineStart - match.Submissions[j].LineStart;
                    int lineEndDiff = lastMatch.Submissions[j].LineFinish - match.Submissions[j].LineFinish;
                    if (lineStartDiff == 0) {
                        if (lineEndDiff >= 0) thisPattern = 1;
                        else thisPattern = 2;
                    } else if (lineStartDiff < 0) { // Line 1 starts before line 2
                        if (lineEndDiff == 0) thisPattern = 1;
                        else if (lineEndDiff < 0) thisPattern = 3; 
                        else thisPattern = 1;
                    } else { // Line 1 starts after line 2
                        if (lineEndDiff == 0) thisPattern = 2;
                        else if (lineEndDiff < 0) thisPattern = 2;
                        else thisPattern = 4;
                    }
                    
                    if (pattern == -1) {
                        pattern = thisPattern;
                    } else if (pattern != thisPattern) {
                        shouldAggregate = false;
                        break;
                    }
                }
                if (!shouldAggregate) {
                    matches.Add(match);
                    continue;
                }

                switch (pattern) {
                    case 1: // Don't add second match
                        break;
                    case 2: // Remove first match, add second match
                        matches.Remove(lastMatch);
                        matches.Add(match);
                        break;
                    case 3: // Extend first match right
                        for (int j = 0; j < lastMatch.Submissions.Count(); j++) {
                            lastMatch.Submissions[j].LineFinish = match.Submissions[j].LineFinish;
                        }
                        break;
                    case 4: // Extend first match left
                        for (int j = 0; j < lastMatch.Submissions.Count(); j++) {
                            lastMatch.Submissions[j].LineStart = match.Submissions[j].LineStart;
                        }
                        break;
                }

            }   

            foreach (var match in matches) {
                Match modelMatch = new Match();
                modelMatch.Lines = new List<Line>();
                foreach (var sub in match.Submissions) {
                    var line = new Line();
                    line.SubmissionId = await DeHash(package, sub.Hash);
                    line.LineStart = sub.LineStart;
                    line.LineEnd = sub.LineFinish;
                    line.FilePath = sub.File.Split(sub.Hash)[1].Substring(1);
                    modelMatch.Lines.Add(line);
                }
                
                result.Matches.Add(modelMatch);
            }
            return result;
        }

        // Looks up the hash, and returns the submission id
        private async Task<long> DeHash(Package package, string hash)
        {
            long result;
            long.TryParse(hash, out result);
            return result;
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
