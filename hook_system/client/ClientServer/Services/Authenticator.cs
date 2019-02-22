using System.Security.Cryptography;
using System.Security.Cryptography.Xml;

namespace ClientServer.Services
{
    public class Authenticator
    {
        private string Encrypt(string username, string password)
        {
            var plainText = System.Text.Encoding.Default.GetBytes(password);
            var salt = System.Text.Encoding.Default.GetBytes(username);
            
            HashAlgorithm algorithm = new SHA256Managed();

            byte[] plainTextWithSaltBytes = 
                new byte[plainText.Length + salt.Length];

            for (int i = 0; i < plainText.Length; i++)
            {
                plainTextWithSaltBytes[i] = plainText[i];
            }
            for (int i = 0; i < salt.Length; i++)
            {
                plainTextWithSaltBytes[plainText.Length + i] = salt[i];
            }

            return System.Text.Encoding.Default.GetString(algorithm.ComputeHash(plainTextWithSaltBytes));  
        }
    }
}