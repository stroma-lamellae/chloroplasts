using System;
using ClientServer.Services;
using Microsoft.AspNetCore.Identity;

namespace ClientServer.Models
{
    public class User
    {
        public long UserId { get; set; }
        public string Firstname { get; set; }
        public string Lastname { get; set; }
        public string Email { get; set; }
        public string Password { get; set; }
        public long RoleId { get; set; }
        public string IdentityId { get; set; }
        
        public AppUser Identity { get; set; }
    }
}