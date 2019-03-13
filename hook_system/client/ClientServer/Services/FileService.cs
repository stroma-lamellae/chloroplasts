using ClientServer.Models;
using System.IO;

/*
This deals with anything to do with writing and saving files
 */

namespace ClientServer.Services
{
    public interface IFileService
    {
        void PersistSubmissionFiles(Submission submission);
    }

    public class FileService : IFileService
    {
        private readonly string _rootStorageDirectory = "Temp";

        // Saves the files in this submission object.
        // The submission needs a valid SubmissionId, as well as the Assignment and Course loaded
        public async void PersistSubmissionFiles(Submission submission)
        {
            var submissionPath = GetSubmissionPath(submission);
            var basePath = Path.Combine(Directory.GetCurrentDirectory(), _rootStorageDirectory, submissionPath);
            submission.FilePath = submissionPath;
                
            // Save each file in the folder
            foreach (var formFile in submission.Files)
            {
                // Actually save the file, if there is anything to save
                // Create the filepath for this file
                var filePath = Path.Combine(basePath, formFile.FileName);

                // Create any necessary folders for this filepath
                Directory.CreateDirectory(filePath);

                // Remove the folder created that is just the file name
                Directory.Delete(filePath);

                if (formFile.Length > 0)
                {
                    using (var stream = new FileStream(filePath, FileMode.Create))
                    {
                        await formFile.CopyToAsync(stream);
                    }
                }
            }
        }

        // Get's the path for where this submission's files should be stored
        private string GetSubmissionPath(Submission submission)
        {
            return Path.Combine(submission.Assignment.Course.Year + "", submission.Assignment.Course.CourseCode.Substring(0, 4), 
                submission.Assignment.Course.CourseCode.Substring(4, 4), submission.Assignment.Name, submission.StudentFirstname +
                "_" + submission.StudentLastname + "_" + submission.StudentNumber);
        }
    }
}