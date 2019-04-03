using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

using ClientServer.Models;
using ClientServer.ViewModels;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;

namespace ClientServer.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    [Authorize(Policy = "User")]
    public class UserController : ControllerBase
    {
        private readonly ClientServerContext _context;
        private readonly UserManager<AppUser> _userManager;
        public UserController(ClientServerContext context, UserManager<AppUser> userManager)
        {
            _context = context;
            _userManager = userManager;
        }
    
        // GET: api/user
        // Gets all of the users
        [HttpGet]
        public async Task<ActionResult<IEnumerable<AppUser>>> GetUsers()
        {
            return await _context.AppUser.ToListAsync();
        }

        // GET: api/user/#
        // Gets the user with the given id
        [HttpGet("{id}")]
        public async Task<ActionResult<AppUser>> GetUser(string id)
        {
            var user = await _userManager.FindByIdAsync(id);

            if (user == null)
            {
                return NotFound();
            }
            return user;
        }

        // POST: api/user
        // Creates an user, and returns where it can be found.
        [HttpPost]
        public async Task<IActionResult> PostUser(RegistrationViewModel user)
        {
            var userIdentity = new AppUser()
            {
                FirstName = user.FirstName,
                LastName = user.LastName,
                Email = user.Email
            };
            
            var result = await _userManager.CreateAsync(userIdentity, user.Password);

            return new OkObjectResult(result);
        }
    }
}