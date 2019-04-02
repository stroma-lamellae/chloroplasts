using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

using ClientServer.Models;
using Microsoft.AspNetCore.Authorization;

namespace ClientServer.Controllers
{
    [Authorize(Policy = "User")]
    [Route("api/[controller]")]
    [ApiController]
    public class RoleController : ControllerBase
    {
        private readonly ClientServerContext _context;

        public RoleController(ClientServerContext context)
        {
            _context = context;
        }

        // GET: api/role
        // Gets all of the roles
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Role>>> GetRoles()
        {
            return await _context.Role.ToListAsync();
        }

        // GET: api/role/#
        // Gets the role with the given id
        [HttpGet("{id}")]
        public async Task<ActionResult<Role>> GetRole(long id)
        {
            var role = await _context.Role.FindAsync(id);

            if (role == null)
            {
                return NotFound();
            }
            return role;
        }

        // POST: api/role
        // Creates an role, and returns where it can be found.
        [HttpPost]
        public async Task<IActionResult> PostRole(Role role)
        {
            _context.Role.Add(role);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetRole), new { id = role.RoleId }, role);
        }

        // PUT: api/role/{id}
        // Update the role with the given id
        [HttpPut("{id}")]
        public async Task<IActionResult> PutRole(long id, Role role)
        {
            if (id != role.RoleId)
            {
                return BadRequest();
            } 

            _context.Entry(role).State = EntityState.Modified;
            await _context.SaveChangesAsync();

            return NoContent();
        }

        // DELETE: api/role/{id}
        // Removes an role and all of the children items
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteRole(long id)
        {
            var role = await _context.Role.FindAsync(id);

            if (role == null)
            {
                return NotFound();
            }

            _context.Role.Remove(role);
            await _context.SaveChangesAsync();

            return NoContent();
        }
    }
}