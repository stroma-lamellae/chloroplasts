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
    public class MatchController : ControllerBase
    {
        private readonly ClientServerContext _context;

        public MatchController(ClientServerContext context)
        {
            _context = context;
        }

        // GET: api/match
        // Gets all of the matchs
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Match>>> GetMatches()
        {
            return await _context.Match.ToListAsync();
        }

        // GET: api/match/#
        // Gets the match with the given id, as well as the lines for it
        [HttpGet("{id}")]
        public async Task<ActionResult<Match>> GetMatch(long id)
        {
            var match = await _context.Match
                .Where(m => m.MatchId == id)
                .Include(m => m.Lines)
                .FirstAsync();

            if (match == null)
            {
                return NotFound();
            }
            return match;
        }
    }
}