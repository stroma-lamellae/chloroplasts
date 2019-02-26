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
<<<<<<< HEAD
<<<<<<< HEAD
        private readonly IProcessingService _processingService;

        public PackageController(ClientServerContext context, 
                                 IHttpClientFactory clientFactory,
                                 IProcessingService processingService)
        {
            _context = context;
            _clientFactory = clientFactory;
            _processingService = processingService;
=======
=======
        private readonly IProcessingService _processingService;
>>>>>>> 75fd07c... Added processing service to communicate with Processing Server. Rewrote PackageController to make use of this.

        public PackageController(ClientServerContext context, 
                                 IHttpClientFactory clientFactory,
                                 IProcessingService processingService)
        {
            _context = context;
            _clientFactory = clientFactory;
<<<<<<< HEAD
>>>>>>> 958925a... Added sample of sending data to another server. Not sending the proper data or anything yet, but it's something!
=======
            _processingService = processingService;
>>>>>>> 75fd07c... Added processing service to communicate with Processing Server. Rewrote PackageController to make use of this.
        }

        // GET: api/package
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Package>>> GetPackages()
        {
            return await _context.Package.ToListAsync();
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

            // Below initiates the upload. Maybe we don't want this to await?
            // Probably, this will be initiated in some other place (possibly a timed service?)
            await _processingService.InitiateUpload(package); 

            return CreatedAtAction(nameof(GetPackage), new { id = package.PackageId }, package);
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