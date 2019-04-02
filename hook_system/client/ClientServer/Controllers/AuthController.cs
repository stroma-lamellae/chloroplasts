using System.Threading.Tasks;
using ClientServer.Services;
using ClientServer.Helpers;
using ClientServer.Models;
using ClientServer.ViewModels;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;

namespace ClientServer.Controllers
{
    [Route("api/[controller]")]
    public class AuthController : ControllerBase
    {
        private readonly UserManager<AppUser> _userManager;
        private readonly AccountService _accountService;
        public AuthController(UserManager<AppUser> userManager, AccountService accountService )
        {
            _userManager = userManager;
            _accountService = accountService;

        }

        [HttpPost("login")]
        public async Task<IActionResult> Post([FromBody]CredentialsViewModel credentials)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            var token = await _accountService.Login(credentials);
            
            if (token == null)
            {
                return BadRequest(Errors.AddErrorToModelState("login_failure", "Invalid username or password.", ModelState));
            }
            // Serialize and return the response
            

            return Ok(token);
        }

    }
}