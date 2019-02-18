using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;

namespace ClientServer.Models
{
    public class ClientServerContext : DbContext
    {
        public ClientServerContext(DbContextOptions<ClientServerContext> options): base (options)
        {

        }

        public DbSet<Course> Courses { get; set; }
        public DbSet<Assignment> Assignments { get; set; }
        public DbSet<Submission> Submissions { get; set; }
        public DbSet<Package> Packages { get; set; }
    }
}