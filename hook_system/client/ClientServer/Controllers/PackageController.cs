using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Net.Http;
using System.Text;
using Newtonsoft.Json;

using ClientServer.Models;
using ClientServer.Services;

namespace ClientServer.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class PackageController: Controller
    {
        private readonly ClientServerContext _context;
        private readonly IHttpClientFactory _clientFactory;
        private readonly IProcessingService _processingService;

        public PackageController(ClientServerContext context, 
                                 IHttpClientFactory clientFactory,
                                 IProcessingService processingService)
        {
            _context = context;
            _clientFactory = clientFactory;
            _processingService = processingService;
        }

        // GET: api/package
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Package>>> GetPackages()
        {
            return await _context.Package.Include(p => p.Result).ToListAsync();
        }

        // GET: api/package/#
        [HttpGet("{id}")]
        public async Task<ActionResult<Package>> GetPackage(long id)
        {
            var package = await _context.Package.FindAsync(id);

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
            _context.Package.Add(package);
            await _context.SaveChangesAsync();
            package = await _context.Package
                .Include(p => p.Assignment)
                    .ThenInclude(a => a.Submissions)
                .Include(p => p.PreviousAssignments)
                    .ThenInclude(pa => pa.Assignment)
                        .ThenInclude(a => a.Submissions)
                .Where(p => p.PackageId == package.PackageId)
                .FirstAsync();

            // Below initiates the upload. Maybe we don't want this to await?
            // Probably, this will be initiated in some other place (possibly a timed service?)
            await _processingService.InitiateUpload(package); 

            return CreatedAtAction(nameof(GetPackage), new { id = package.PackageId }, package);
        }

        // GET: api/package/{id}/results
        // Requests the results for a package
        [HttpGet("{id}/results")]
        public async Task<ActionResult<Package>> RequestResults(long id)
        {
            var package = await _context.Package.FindAsync(id);

            if (package == null)
            {
                return NotFound();
            }

            var response = await _processingService.RequestResults(package.JobId);
            if (response.Result != null) {
                package.Result = response.Result;
                _context.Entry(package).State = EntityState.Modified;
                await _context.SaveChangesAsync();
            }
            return package;
        }

        // DELETE: api/package/{id}
        // Deletes a package and all of it's associated information
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeletePackage(long id)
        {
            var package = await _context.Package.FindAsync(id);

            if (package == null)
            {
                return NotFound();
            }

            _context.Package.Remove(package);
            await _context.SaveChangesAsync();

            return NoContent();
        }
    }
}