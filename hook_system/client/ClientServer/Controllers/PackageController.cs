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

            // Below initiates the upload. Maybe we don't want this to await?
            // Probably, this will be initiated in some other place (possibly a timed service?)
            await _processingService.InitiateUpload(package); 

            return CreatedAtAction(nameof(GetPackage), new { id = package.PackageId }, package);
        }
    }
}