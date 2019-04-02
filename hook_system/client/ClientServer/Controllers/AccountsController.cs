using System.Threading.Tasks;
using ClientServer.Helpers;
using ClientServer.Models;
using ClientServer.Services;
using ClientServer.ViewModels;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;

namespace ClientServer.Controllers
{
   // [Authorize(Policy = "ApiUser")]
    [Route("api/[controller]")]
    public class AccountsController : ControllerBase
    {
        private readonly ClientServerContext _dbContext;
        private readonly UserManager<AppUser> _userManager;
    
        public AccountsController(ClientServerContext dbContext, UserManager<AppUser> userManager)
        {
            _dbContext = dbContext;
            _userManager = userManager;
        }
        [HttpPost]
        public async Task<IActionResult> Post([FromBody]RegistrationViewModel model)
        {

            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }
            
            var userIdentity = new AppUser()
            {
                UserName = model.Email,
                Email = model.Email,
                FirstName = model.FirstName,
                LastName = model.LastName,
                Role = model.Role
            };

            var result = await _userManager.CreateAsync(userIdentity, model.Password);
            


            if (!result.Succeeded)
            {
                return new BadRequestObjectResult(Errors.AddErrorsToModelState(result, ModelState));
            }

            return new OkObjectResult("Account created");
        }
    }
}