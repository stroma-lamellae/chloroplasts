using System.IO;
using System.Linq;
using System.Threading.Tasks;
using ClientServer.Models;
using ClientServer.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;

namespace ClientServer.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    [Authorize(Policy = "User")]
    public class FileController : ControllerBase
    {
        private readonly ClientServerContext _context;
        private readonly IFileService _fileService;

        public FileController(ClientServerContext context, IFileService fileService)
        {
            _context = context;
            _fileService = fileService;
        }
        
        
        // GET: api/file/#
        [HttpGet("{submissionId}")]
        public async Task<ActionResult<Submission>> GetFile(long submissionId, string filePath)
        {
            var submission = await _context.Submission.FindAsync(submissionId);
            var splitPaths = filePath.Split(Path.DirectorySeparatorChar);
            var str = splitPaths.Last();
            var path = Path.Join(submission.FilePath, str.Substring(str.IndexOf('-')+1));
            
            if (submission == null)
            {
                return NotFound();
            }

            var file = await _fileService.ReadFileFromStorageAsync(path);
            
            // Serialize and return the response
            var jsonObject = new
            {
                submissionId = submission.SubmissionId,
                lines = file,
                filePath = submission.FilePath
            };
            var json = JsonConvert.SerializeObject(jsonObject);
            return new OkObjectResult(json);
        }
    }
}