using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

using ClientServer.Models;
using Microsoft.AspNetCore.Authorization;

namespace ClientServer.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    [Authorize(Policy = "User")]
    public class AssignmentController : ControllerBase
    {
        private readonly ClientServerContext _context;

        public AssignmentController(ClientServerContext context)
        {
            _context = context;
        }

        // GET: api/assignment/#
        // Gets the assignment with the given id
        [HttpGet("{id}")]
        public async Task<ActionResult<Assignment>> GetAssignment(long id)
        {
            var assignment = await _context.Assignment.FindAsync(id);

            if (assignment == null)
            {
                return NotFound($"No assignment with id {id}");
            }
            return assignment;
        }

        // POST: api/assignment
        // Creates an assignment, and returns where it can be found.
        [HttpPost]
        public async Task<IActionResult> PostAssignment(Assignment assignment)
        {
            _context.Assignment.Add(assignment);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetAssignment), new { id = assignment.AssignmentId }, assignment);
        }

        // PUT: api/assignment/{id}
        // Update the assignment with the given id
        [HttpPut("{id}")]
        public async Task<IActionResult> PutAssignment(long id, Assignment assignment)
        {
            if (id != assignment.AssignmentId)
            {
                return BadRequest($"AssignmentId ({assignment.AssignmentId}) doesn't match Id ({id})");
            } 

            _context.Entry(assignment).State = EntityState.Modified;
            await _context.SaveChangesAsync();

            return NoContent();
        }

        // DELETE: api/assignment/{id}
        // Removes an assignment and all of the children items
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteAssignment(long id)
        {
            var assignment = await _context.Assignment.FindAsync(id);

            if (assignment == null)
            {
                return NotFound($"No assignment with id {id}");
            }

            _context.Assignment.Remove(assignment);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        // GET: api/assignment/#/submissions
        // Returns the submissions for an assignment
        [HttpGet("{id}/submissions")]
        public async Task<ActionResult<Assignment>> GetSubmissions(long id)
        {
            // Get the submissions for this assignment
            var submissions = await _context.Assignment
                .Where(a => a.AssignmentId == id)
                .Include(a => a.Submissions)
                .FirstAsync();

            return submissions;
        }
    }
}