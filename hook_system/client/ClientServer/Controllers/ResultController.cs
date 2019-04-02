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
    public class ResultController : ControllerBase
    {
        private readonly ClientServerContext _context;

        public ResultController(ClientServerContext context)
        {
            _context = context;
        }

        // GET: api/result
        // Gets all of the results
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Result>>> GetResults()
        {
            return await _context.Result.ToListAsync();
        }

        // GET: api/result/#
        // Gets the result with the given id
        [HttpGet("{id}")]
        public async Task<ActionResult<Result>> GetResult(long id)
        {
            var result = await _context.Result.FindAsync(id);

            if (result == null)
            {
                return NotFound();
            }
            return result;
        }

        // GET: api/result/#/matches
        // Gets the result with all of its matches
        [HttpGet("{id}")]
        public async Task<ActionResult<Result>> GetMatches(long id)
        {
            var result = await _context.Result
                .Where(r => r.ResultId == id)
                .Include(r => r.Matches)
                .FirstAsync();

            return result;
        }
    }
}