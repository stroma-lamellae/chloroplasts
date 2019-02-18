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
        private readonly IProcessingService _processingService;

        public PackageController(ClientServerContext context, 
                                 IHttpClientFactory clientFactory,
                                 IProcessingService processingService)
        {
            _context = context;
            _clientFactory = clientFactory;
            _processingService = processingService;
=======

        public PackageController(ClientServerContext context, IHttpClientFactory clientFactory)
        {
            _context = context;
            _clientFactory = clientFactory;
>>>>>>> 958925a... Added sample of sending data to another server. Not sending the proper data or anything yet, but it's something!
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

            // May need to fix this
            await SendPackage(package);

            return CreatedAtAction(nameof(GetPackage), new { id = package.PackageId }, package);
        }

        // Sends a package to some server
        // This is intended to be an example as to how we will send data to the processing server
        // Right now, this is the incorrect data, and we will probably want to have this send
        //   in a different location.
        // TODO: Move this to a Service, and have it remove tasks from a queue
        private async Task SendPackage(Package package)
        {
            var client = _clientFactory.CreateClient();

            var response = await client.PostAsync("http://localhost:3000/submit", new StringContent(JsonConvert.SerializeObject(package), Encoding.UTF8, "application/json"));
        }
    }
}