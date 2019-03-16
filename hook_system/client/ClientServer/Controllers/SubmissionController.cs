using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

using ClientServer.Models;
using ClientServer.Services;

namespace ClientServer.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class SubmissionController : ControllerBase
    {
        private readonly ClientServerContext _context;
        private readonly IFileService _fileService;

        public SubmissionController(ClientServerContext context, IFileService fileService)
        {
            _context = context;
            _fileService = fileService;
        }
        
        // GET: api/submission/#
        [HttpGet("{id}")]
        public async Task<ActionResult<Submission>> GetSubmission(long id)
        {
            var submission = await _context.Submission.FindAsync(id);

            if (submission == null)
            {
                return NotFound();
            }
            return submission;
        }

        // POST: api/submission
        // Adds a submission to the database, and stores all of the files
        // File stuff is based off of:
        //      https://docs.microsoft.com/en-us/aspnet/core/mvc/models/file-uploads?view=aspnetcore-2.2
        [HttpPost]
        [DisableRequestSizeLimit]
        public async Task<IActionResult> PostSubmission([FromForm] Submission submission) //, Submission submission
        {
            _context.Submission.Add(submission);
            await _context.SaveChangesAsync();
            // Load required info the persist files
            submission = await _context.Submission
                .Include(s => s.Assignment)
                    .ThenInclude(a => a.Course)
                .Where(s => s.SubmissionId == submission.SubmissionId)
                .FirstAsync();
                

            _fileService.PersistSubmissionFiles(submission);
            // Save the submission again, because it has been updated with a file path
            _context.Entry(submission).State = EntityState.Modified;
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetSubmission), new { id = submission.SubmissionId }, submission);
        }

        // PUT: api/submission/{id}/files
        // Adds files to a submission. Assumes that the submission already exists
        [HttpPut("{id}/files")]
        [DisableRequestSizeLimit]
        public async Task<IActionResult> PostSubmissionFiles(long id, List<IFormFile> files)
        {
            var submission = await _context.Submission
                .Include(s => s.Assignment)
                    .ThenInclude(a => a.Course)
                .Where(s => s.SubmissionId == id)
                .FirstAsync();

            if (submission == null)
            {
                return NotFound();
            }

            submission.Files = files;

            _fileService.PersistSubmissionFiles(submission);

            return Ok();
        }

        // PUT: api/submission/{id}
        // Update the submission with the given id
        [HttpPut("{id}")]
        public async Task<IActionResult> PutSubmission(long id, Submission submission)
        {
            if (id != submission.SubmissionId)
            {
                return BadRequest();
            }

            _context.Entry(submission).State = EntityState.Modified;
            await _context.SaveChangesAsync();

            return NoContent();
        }

        // DELETE: api/submission/{id}
        // Deletes a submission
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteSubmission(long id)
        {
            var submission = await _context.Submission.FindAsync(id);

            if (submission == null)
            {
                return NotFound();
            }

            _context.Submission.Remove(submission);
            await _context.SaveChangesAsync();

            return NoContent();
        }
    }
}