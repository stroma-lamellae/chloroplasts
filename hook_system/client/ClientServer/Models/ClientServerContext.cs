using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using Microsoft.Extensions.Configuration;

namespace ClientServer.Models
{
    public class ClientServerContext : DbContext
    {
        public ClientServerContext(DbContextOptions<ClientServerContext> options): base (options)
        {

        }
        
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Package>()
                .HasOne(a => a.Result)
                .WithOne(b => b.Package)
                .HasForeignKey<Result>(b => b.PackageId);
        }

        public DbSet<Assignment> Assignments { get; set; }
        public DbSet<Course> Courses { get; set; }
        public DbSet<Exclusion> Exclusions { get; set; }
        public DbSet<Line> Lines { get; set; }
        public DbSet<Match> Matches { get; set; }
        public DbSet<Package> Packages { get; set; }
        public DbSet<PackageExclusion> PackageExclusions { get; set; }
        public DbSet<PreviousAssignment> PreviousAssignments { get; set; }
        public DbSet<Result> Results { get; set; }
        public DbSet<Role> Roles { get; set; }
        public DbSet<Submission> Submissions { get; set; }
        public DbSet<User> Users { get; set; }
    }
}