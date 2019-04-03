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
    public class ExclusionController : ControllerBase
    {
        private readonly ClientServerContext _context;

        public ExclusionController(ClientServerContext context)
        {
            _context = context;
        }

        // GET: api/exclusion
        // Gets all of the exclusions
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Exclusion>>> GetExclusions()
        {
            return await _context.Exclusion.ToListAsync();
        }

        // GET: api/exclusion/#
        // Gets the exclusion with the given id
        [HttpGet("{id}")]
        public async Task<ActionResult<Exclusion>> GetExclusion(long id)
        {
            var exclusion = await _context.Exclusion.FindAsync(id);

            if (exclusion == null)
            {
                return NotFound();
            }
            return exclusion;
        }

        // POST: api/exclusion
        // Creates an exclusion, and returns where it can be found.
        [HttpPost]
        public async Task<IActionResult> PostExclusion(Exclusion exclusion)
        {
            _context.Exclusion.Add(exclusion);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetExclusion), new { id = exclusion.ExclusionId }, exclusion);
        }

        // PUT: api/exclusion/{id}
        // Update the exclusion with the given id
        [HttpPut("{id}")]
        public async Task<IActionResult> PutExclusion(long id, Exclusion exclusion)
        {
            if (id != exclusion.ExclusionId)
            {
                return BadRequest();
            } 

            _context.Entry(exclusion).State = EntityState.Modified;
            await _context.SaveChangesAsync();

            return NoContent();
        }

        // DELETE: api/exclusion/{id}
        // Removes an exclusion and all of the children items
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteExclusion(long id)
        {
            var exclusion = await _context.Exclusion.FindAsync(id);

            if (exclusion == null)
            {
                return NotFound();
            }

            _context.Exclusion.Remove(exclusion);
            await _context.SaveChangesAsync();

            return NoContent();
        }
    }
}