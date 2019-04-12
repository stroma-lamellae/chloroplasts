using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Net;
using System.Net.Http;
using System.Text;
using Newtonsoft.Json;

using ClientServer.Models;
using ClientServer.Services;
using Microsoft.AspNetCore.Authorization;

namespace ClientServer.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    [Authorize(Policy = "User")]
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
            return await _context.Package
                .Include(p => p.Assignment)
                .ThenInclude(a => a.Course)
                .Include(p => p.Result)
                    .ThenInclude(r => r.Matches)
                .OrderByDescending(p => p.PackageId)
                .ToListAsync();
        }

        // GET: api/package/#
        [HttpGet("{id}")]
        public async Task<ActionResult<Package>> GetPackage(long id)
        {
            var package = await _context.Package.FindAsync(id);

            if (package == null)
            {
                return NotFound($"No package with id {id}");
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
            var result = await _processingService.InitiateUpload(package); 
            
            if (result.StatusCode != HttpStatusCode.OK) {
                return BadRequest($"Processing Server Response: {result.Status}");
            }
            // Otherwise, the upload was successful
            package.JobId = result.JobId;
            package.EstimatedCompletion = result.EstimatedCompletionTime;
            _context.Entry(package).State = EntityState.Modified;
            await _context.SaveChangesAsync();

            return CreatedAtAction(nameof(GetPackage), new { id = package.PackageId }, package);
        }

        // GET: api/package/{id}/results
        // Requests the results for a package
        [HttpGet("{id}/results")]
        public async Task<ActionResult> RequestResults(long id)
        {
            var package = await _context.Package
                .Include(p => p.Assignment)
                    .ThenInclude(a => a.Course)
                .Include(p => p.Result)
                    .ThenInclude(r => r.Matches)
                        .ThenInclude(m => m.Lines)
                            .ThenInclude(l => l.Submission)
                .SingleOrDefaultAsync(p => p.PackageId == id);

            if (package == null)
            {
                return NotFound($"No package with id {id}");
            }

            var response = await _processingService.RequestResults(package.JobId);

            if (response.StatusCode != HttpStatusCode.OK) {
                return BadRequest($"Processing Server Response: {response.Status}");
            } 
            if (response.Status.Equals("Ok")) {
                package.Result = response.Result;
            } else {
                package.EstimatedCompletion = response.EstimatedCompletion;
            }
            _context.Entry(package).State = EntityState.Modified;
            await _context.SaveChangesAsync();
            return Ok(package);
        }

        // DELETE: api/package/{id}
        // Deletes a package and all of it's associated information
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeletePackage(long id)
        {
            var package = await _context.Package.FindAsync(id);

            if (package == null)
            {
                return NotFound($"No package with id {id}");
            }

            _context.Package.Remove(package);
            await _context.SaveChangesAsync();

            return NoContent();
        }
    }
}