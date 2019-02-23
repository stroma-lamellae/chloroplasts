using System.Threading.Tasks;
using ClientServer.Models;
using Microsoft.AspNetCore.Mvc;

namespace ClientServer.Controllers
{
    
    public class AuthenticationController : ControllerBase
    {
        private readonly ClientServerContext _context;

        public AuthenticationController(ClientServerContext context)
        {
            _context = context;
        }

        [HttpPost]
        public async Task<IActionResult> Authenticate()
        {
            return null;
        }
    }
}