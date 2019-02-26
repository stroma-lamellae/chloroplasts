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

        public DbSet<Assignment> Assignment { get; set; }
        public DbSet<Course> Course { get; set; }
        public DbSet<Exclusion> Exclusion { get; set; }
        public DbSet<Line> Line { get; set; }
        public DbSet<Match> Match { get; set; }
        public DbSet<Package> Package { get; set; }
        public DbSet<PackageExclusion> PackageExclusion { get; set; }
        public DbSet<PreviousAssignment> PreviousAssignment { get; set; }
        public DbSet<Result> Result { get; set; }
        public DbSet<Role> Role { get; set; }
        public DbSet<Submission> Submission { get; set; }
        public DbSet<User> User { get; set; }
    }
}