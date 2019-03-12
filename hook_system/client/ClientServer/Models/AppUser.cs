using Microsoft.AspNetCore.Identity;

namespace ClientServer.Services
{
    public class AppUser : IdentityUser
    {
        public string FirstName { get; set; }
        public string LastName { get; set; }
    }
}