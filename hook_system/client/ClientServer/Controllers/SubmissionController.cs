using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

using ClientServer.Models;

namespace ClientServer.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class SubmissionController : ControllerBase
    {
        private readonly ClientServerContext _context;

        public SubmissionController(ClientServerContext context)
        {
            _context = context;
        }
        
        // GET: api/submission/#
        [HttpGet("{id}")]
        public async Task<ActionResult<Submission>> GetSubmission(long id)
        {
            var submission = await _context.Submissions.FindAsync(id);

            if (submission == null)
            {
                return NotFound();
            }
            return submission;
        }

        // POST: api/submission
        // Adds a submission to the database
        [HttpPost]
        public async Task<IActionResult> PostSubmission(Submission submission)
        {
            _context.Submissions.Add(submission);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetSubmission), new { id = submission.SubmissionId }, submission);
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
            var submission = await _context.Submissions.FindAsync(id);

            if (submission == null)
            {
                return NotFound();
            }

            _context.Submissions.Remove(submission);
            await _context.SaveChangesAsync();

            return NoContent();
        }
    }
}