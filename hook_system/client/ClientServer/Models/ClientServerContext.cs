using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;

namespace ClientServer.Models
{
    public class ClientServerContext : IdentityDbContext<AppUser>
    {
        private readonly IHttpContextAccessor _httpContextAccessor;
        public ClientServerContext(DbContextOptions<ClientServerContext> options, IHttpContextAccessor httpContextAccessor): base (options)
        {
            _httpContextAccessor = httpContextAccessor;
        }
        
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Package>()
                .HasOne(a => a.Result)
                .WithOne(b => b.Package)
                .HasForeignKey<Result>(b => b.PackageId);
            
            // Set up so that only the owner can access their stuff
            modelBuilder.Entity<Assignment>().HasQueryFilter(a => a.Course.UserId ==  getUserId());
            modelBuilder.Entity<Course>().HasQueryFilter(c => c.UserId ==  getUserId());
            modelBuilder.Entity<Line>().HasQueryFilter(l => l.Submission.Assignment.Course.UserId == getUserId());
            modelBuilder.Entity<Match>().HasQueryFilter(m => m.Result.Package.Assignment.Course.UserId == getUserId());
            modelBuilder.Entity<Package>().HasQueryFilter(p => p.Assignment.Course.UserId == getUserId());
            modelBuilder.Entity<PackageExclusion>().HasQueryFilter(p => p.Package.Assignment.Course.UserId == getUserId());
            modelBuilder.Entity<PreviousAssignment>().HasQueryFilter(p => p.Assignment.Course.UserId == getUserId());
            modelBuilder.Entity<Result>().HasQueryFilter(r => r.Package.Assignment.Course.UserId == getUserId());
            modelBuilder.Entity<Submission>().HasQueryFilter(s => s.Assignment.Course.UserId == getUserId());
            // TODO: Add Exclusion
            // TODO: Add StudentHashMapping
            
            base.OnModelCreating(modelBuilder);
        }

        private string getUserId() {
            return _httpContextAccessor.HttpContext.User.FindFirst("userId").Value;
        }
        
        public DbSet<AppUser> AppUser { get; set; }
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
        public DbSet<StudentHashMapping> StudentHashMapping {get;set;}
    }
}