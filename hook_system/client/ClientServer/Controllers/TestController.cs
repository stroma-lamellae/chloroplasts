using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Threading.Tasks;

using ClientServer.Models;
using ClientServer.Services;

namespace ClientServer.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    [Authorize(Policy = "User")]
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
        public async Task<IActionResult> PostTest([FromForm] TestData data)
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
                Name = data.TestName,
            };
            course.Assignments.Add(assignment);

            // Create all of our submissions based on what was in the zip
            string extractedFilePath;
            try {
                extractedFilePath = _fileService.ExtractFile(data.File);
            } catch (InvalidOperationException) {
                return BadRequest("Incorrect File Type. Should be valid compressed folder (i.e. zip)");
            }
            List<Submission> submissions = new List<Submission>();
            
            // Create a submission for each directory
            var directories = Directory.GetDirectories(extractedFilePath);
            // In case the zipping of files led to a parent folder within the zip
            if (directories.Length == 1) { 
                extractedFilePath = directories[0];
                directories = Directory.GetDirectories(extractedFilePath);
            }
            foreach (var directory in directories)
            {
                // Use the relative path as the student number, since that will be unique
                string relativePath = directory.Split(extractedFilePath)[1];
                // Replace any underscores because the Processing server looks for exactly 3 underscores,
                //  and we insert underscores based on the FirstName, LastName and StudetNumber
                relativePath = relativePath.Replace("\\", "").Replace("/", "").Replace("_", "&underscore&");
                
                // Create the Submission for this folder
                var submission = new Submission {
                    StudentFirstname = $"ThisIsTestData{data.TestName}",
                    StudentLastname = $"ThisIsTestData{data.TestName}",
                    StudentNumber = relativePath
                };
                submissions.Add(submission);

                // Create a mapping so that it can tie into the current pipeline
                var mapping = new StudentHashMapping()
                {
                    Firstname = submission.StudentFirstname,
                    Lastname = submission.StudentLastname,
                    StudentNumber = submission.StudentNumber,
                    Hash_Firstname = submission.StudentFirstname,
                    Hash_Lastname = submission.StudentLastname,
                    Hash_StudentNumber = submission.StudentNumber
                };
                _context.StudentHashMapping.Add(mapping);
            }
            
            // Add all of the submissions we just created
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
                _fileService.PersistSubmissionFiles(submission, extractedFilePath, submission.StudentNumber.Replace("&underscore&", "_"));
                _context.Entry(submission).State = EntityState.Modified;
            }

            // Save the filepaths for the submissions
            await _context.SaveChangesAsync();

            var package = new Package() {
                Assignment = assignment
            };

            _context.Package.Add(package);
            await _context.SaveChangesAsync();

            // Upload the package
            var result = await _processingService.InitiateUpload(package, false);

            if (result.StatusCode != HttpStatusCode.OK) {
                return BadRequest($"Processing Server Response: {result.Status}");
            }
            // Copy the info into our package
            package.JobId = result.JobId;
            package.EstimatedCompletion = result.EstimatedCompletionTime;
            _context.Entry(package).State = EntityState.Modified;
            await _context.SaveChangesAsync();

            return Ok(package);
        }

    }

    // The format for a test data submission
    public class TestData {
        public IFormFile File { get; set; }
        public string Email { get; set; }
        public string TestName { get; set; }
    }
}