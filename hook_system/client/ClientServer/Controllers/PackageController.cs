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
    public class PackageController: ControllerBase
    {
        private readonly ClientServerContext _context;

        public PackageController(ClientServerContext context)
        {
            _context = context;
        }

        // GET: api/package
        public async Task<ActionResult<IEnumerable<Package>>> GetPackages()
        {
            return await _context.Packages.ToListAsync();
        }

        // GET: api/package/#
        [HttpGet("{id}")]
        public async Task<ActionResult<Package>> GetPackage(long id)
        {
            var package = await _context.Packages.FindAsync(id);

            if (package == null)
            {
                return NotFound();
            }
            return package;
        }

        // POST: api/package
        // Creates a package
        [HttpPost]
        public async Task<IActionResult> PostPackage(Package package)
        {
            _context.Packages.Add(package);
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetPackage), new { id = package.PackageId }, package);
        }
    }
}