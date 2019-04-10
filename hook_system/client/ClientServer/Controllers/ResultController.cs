using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using ClientServer.Models;
using ClientServer.Services;
using Microsoft.AspNetCore.Authorization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using FileResult = ClientServer.Services.FileResult;

namespace ClientServer.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    [Authorize(Policy = "User")]
    public class ResultController : ControllerBase
    {
        private readonly ClientServerContext _context;
        private readonly IProcessingService _processingService;
        private readonly IFileService _fileService;

        public ResultController(ClientServerContext context, IProcessingService processingService,
            IFileService fileService)
        {
            _context = context;
            _processingService = processingService;
            _fileService = fileService;
        }

        // GET: api/result
        // Gets all of the results
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Result>>> GetResults()
        {
            return await _context.Result.ToListAsync();
        }

        // GET: api/result/#
        // Gets the result with the given id
        [HttpGet("{id}")]
        public async Task<ActionResult<Result>> GetResult(long id)
        {
            var result = await _context.Result.FindAsync(id);

            if (result == null)
            {
                return NotFound($"No results with id {id}");
            }

            return result;
        }

        // GET: api/result/#/matches
        // Gets the result with all of its matches
        [HttpGet("{id}")]
        public async Task<ActionResult<Result>> GetMatches(long id)
        {
            var result = await _context.Result
                .Where(r => r.ResultId == id)
                .Include(r => r.Matches)
                .FirstAsync();

            return result;
        }

        // GET: api/result/#/package
        // Gets the result with all of its matches
        [HttpGet("{id}/package")]
        public async Task<ActionResult<string>> GetByPackageId(long id)
        {
            var package = await _context.Package
                .Include(p => p.Assignment)
                .ThenInclude(a => a.Course)
                .Include(p => p.Result)
                .ThenInclude(r => r.Matches)
                .ThenInclude(m => m.Lines)
                .ThenInclude(l => l.Submission)
                .SingleOrDefaultAsync(p => p.PackageId == id);

            if (package == null)
            {
                return NotFound();
            }

            var response = await _processingService.RequestResults(package.JobId);
            if (response.Result != null)
            {
                package.Result = response.Result;
                _context.Entry(package).State = EntityState.Modified;
                await _context.SaveChangesAsync();
            }

            var submissionIds = new List<long>();
            var files = new List<FileResult>();

            foreach (var match in package.Result.Matches)
            {
                foreach (var line in match.Lines)
                {
                    if (!submissionIds.Contains(line.SubmissionId))
                    {
                        var submission = await _context.Submission.FindAsync(line.SubmissionId);
                        if (submission == null)
                        {
                            return NotFound();
                        }

                        submissionIds.Add(line.SubmissionId);
                        files.Add(await _fileService.ReadFileFromStorageAsync(line.SubmissionId, line.FilePath,
                            submission.FilePath));
                    }
                }
            }

            var jsonResponse = new
            {
                assignmentName = package.Assignment.Name,
                courseCode = package.Assignment.Course.CourseCode,
                programCode = package.Assignment.Course.ProgramCode,
                matches = package.Result.Matches,
                files = files
            };

            var json = JsonConvert.SerializeObject(jsonResponse,
                new JsonSerializerSettings() {ContractResolver = new CamelCasePropertyNamesContractResolver()});
            return new OkObjectResult(json);
        }
    }
}