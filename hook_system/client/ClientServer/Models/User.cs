using System;
using ClientServer.Services;
using Microsoft.AspNetCore.Identity;
using System.ComponentModel.DataAnnotations.Schema;

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
        [NotMapped]
        public string IdentityId { get; set; }
        [NotMapped]
        public AppUser Identity { get; set; }
    }
}