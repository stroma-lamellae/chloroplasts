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
    }
}