using System.Threading.Tasks;
using ClientServer.Services;
using ClientServer.Helpers;
using ClientServer.Models;
using ClientServer.ViewModels;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;

namespace ClientServer.Controllers
{
    [Route("api/[controller]")]
    public class AuthController : ControllerBase
    {
        private readonly UserManager<AppUser> _userManager;
        private readonly JsonSerializerSettings _serializerSettings;
        private readonly AccountService _accountService;
        public AuthController(UserManager<AppUser> userManager, AccountService accountService )
        {
            _userManager = userManager;
            _accountService = accountService;
            _serializerSettings = new JsonSerializerSettings
            {
                Formatting = Formatting.Indented
            };
        }

        [HttpPost("login")]
        public async Task<IActionResult> Post([FromBody]CredentialsViewModel credentials)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            var response = await _accountService.Login(credentials);
            
            if (response == null)
            {
                return BadRequest(Errors.AddErrorToModelState("login_failure", "Invalid username or password.", ModelState));
            }
            // Serialize and return the response
            var jsonObject = new
            {
                id = response.Item1,
                auth_token = response.Item2,
                expires_in = response.Item3
            };
            var json = JsonConvert.SerializeObject(jsonObject, _serializerSettings);
            return new OkObjectResult(json);
        }

    }
}