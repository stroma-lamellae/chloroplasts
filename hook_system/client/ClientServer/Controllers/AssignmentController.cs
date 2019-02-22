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
    public class AssignmentController : ControllerBase
    {
        private readonly ClientServerContext _context;

        public AssignmentController(ClientServerContext context)
        {
            _context = context;
        }

        // GET: api/assignment/#
        [HttpGet("{id}")]
        public async Task<ActionResult<Assignment>> GetAssignment(long id)
        {
            var assignment = await _context.Assignments.FindAsync(id);

            if (assignment == null)
            {
                return NotFound();
            }
            return assignment;
        }

        // POST: api/assignment
        // Creates an assignment
        [HttpPost]
        public async Task<IActionResult> PostAssignment(Assignment assignment)
        {
            _context.Assignments.Add(assignment);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetAssignment), new { id = assignment.AssignmentId }, assignment);
        }

        // GET: api/assignment/#/submissions
        // Returns the submission ids for an assignment
        [HttpGet("{id}/submissions")]
        public async Task<ActionResult<IEnumerable<long>>> GetSubmissionIds(long id)
        {
            var assignment = _context.Assignments.Find(id);

            if (assignment == null)
            {
                return NotFound();
            }

            var submissions =   await (from a in _context.Submissions
                select a).ToListAsync();

            var ids = submissions.Where(x => x.Assignment == assignment).Select(x => x.SubmissionId).ToList();

            return ids;
        }
    }
}