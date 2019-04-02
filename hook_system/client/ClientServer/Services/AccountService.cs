using Microsoft.Extensions.Configuration;
using Microsoft.IdentityModel.Tokens;
using System;
using System.Collections.Generic;
using System.IdentityModel.Tokens.Jwt;
using System.Linq;
using System.Security.Claims;
using System.Text;
using System.Threading.Tasks;
using ClientServer.Models;
using ClientServer.ViewModels;
using Microsoft.AspNetCore.Identity;

namespace ClientServer.Services
{
    public class AccountService
    {

        private readonly UserManager<AppUser> _userManager;
        private readonly SecurityKey _signingKey;
        private readonly int _expiryDuration;
        public AccountService(IConfiguration configuration, UserManager<AppUser> userManager)
        {
            var options = configuration.GetSection("JwtConfigurations");
            var secretKey = options["SigningKey"];
            _signingKey = new SymmetricSecurityKey(Encoding.ASCII.GetBytes(secretKey));
            _expiryDuration = int.Parse(options["ExpiryDuration"]);
            _userManager = userManager;
        }

        public async Task<Tuple<string,string,int>> Login(CredentialsViewModel login)
        {
            var response = await GetClaimsIdentity(login.Email, login.Password);
           
            return response;
        }
        
        private async Task<Tuple<string,string,int>>GetClaimsIdentity(string email, string password)
        {
            if (string.IsNullOrEmpty(email) || string.IsNullOrEmpty(password))
                return null;

            // get the user to verify
            var user = await _userManager.FindByNameAsync(email);

            if (user == null) return null; 

            // check the credentials
            if (!await _userManager.CheckPasswordAsync(user, password)) return null;
            var tokenDescriptor = new SecurityTokenDescriptor
            {
                Issuer = null,              // Not required as no third-party is involved
                Audience = null,            // Not required as no third-party is involved
                IssuedAt = DateTime.UtcNow,
                NotBefore = DateTime.UtcNow,
                Expires = DateTime.UtcNow.AddMinutes(_expiryDuration),
                Subject = new ClaimsIdentity(new List<Claim> {
                    new Claim("userid", user.Id.ToString()),
                    new Claim("role", user.Role)
                }),
                SigningCredentials = new SigningCredentials(_signingKey, SecurityAlgorithms.HmacSha256Signature)
            };
            var jwtTokenHandler = new JwtSecurityTokenHandler();
            var jwtToken = jwtTokenHandler.CreateJwtSecurityToken(tokenDescriptor);
            var token = jwtTokenHandler.WriteToken(jwtToken);

            return new Tuple<string, string, int>(user.Id,token,_expiryDuration);
        }
    }
}
