using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Newtonsoft.Json;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

using ClientServer.Models;
using ClientServer.Services;

namespace ClientServer.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class TestController : ControllerBase
    {
        private readonly ClientServerContext _context;

        private readonly IFileService _fileService;

        private readonly IProcessingService _processingService;

        public TestController(ClientServerContext context, IFileService fileService, IProcessingService processingService)
        {
            _context = context;
            _fileService = fileService;
            _processingService = processingService;
        }

        // POST: api/test
        // Handles a post request to submit a testing zip file
        [HttpPost]
        [DisableRequestSizeLimit]
        public async Task<IActionResult> PostTest([FromForm] IFormFile file)
        {
            // Get TEST course, or create it if it doesn't exist
            var courses = (await _context.Course
                .Where(c => c.CourseCode.Equals("TEST"))
                .Where(c => c.ProgramCode.Equals("TEST"))
                .Include(c => c.Assignments)
                .ToListAsync());

            Course course;

            if (courses.Count() == 0)
            {
                course = new Course() {
                    Year = 2019,
                    Semester = 1,
                    ProgramCode = "TEST",
                    CourseCode = "TEST"
                };
                _context.Course.Add(course);
                course.Assignments = new List<Assignment>();
            } else {
                course = courses[0];
                _context.Entry(course).State = EntityState.Modified;
            }

            // Create the assignment for this test
            var assignment = new Assignment() {
                Name = file.FileName,
            };
            course.Assignments.Add(assignment);

            // Create all of our submissions based on what was in the zip
            var extractedFilePath = _fileService.ExtractFile(file);
            List<Submission> submissions = new List<Submission>();
            
            var directories = Directory.GetDirectories(extractedFilePath);
            foreach (var directory in directories)
            {
                string relativePath = directory.Split(extractedFilePath)[1];
                // Create the Submission for this folder
                var submission = new Submission {
                    StudentFirstname = "a",
                    StudentLastname = "a",
                    StudentNumber = relativePath.Replace("\\", "")
                };
                submissions.Add(submission);
            }
            
            assignment.Submissions = submissions;
            await _context.SaveChangesAsync();

            // Get a list of the submission Ids
            var submissionIds = submissions.Select(s => s.SubmissionId).ToList();

            // Load required info to persist files
            submissions = await _context.Submission
                .Include(s => s.Assignment)
                    .ThenInclude(a => a.Course)
                .Where(s => submissionIds.Contains(s.SubmissionId))
                .ToListAsync();
            
            // Persist all submission files
            foreach (var submission in submissions)
            {
                // _fileService.PersistSubmissionFiles(submission, extractedFilePath, submission.StudentNumber);
                _context.Entry(submission).State = EntityState.Modified;
            }

            // Save the filepaths for the submissions
            await _context.SaveChangesAsync();

            var package = new Package() {
                Assignment = assignment
            };

            _context.Package.Add(package);
            await _context.SaveChangesAsync();

            // Upload assignment
            await _processingService.InitiateUpload(package, false);

            return Ok(package);
        }


    }
}