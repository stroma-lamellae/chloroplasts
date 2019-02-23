using System;

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
    }
}