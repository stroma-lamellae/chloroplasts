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
        // The submission needs a valid SubmissionId
        public async void PersistSubmissionFiles(Submission submission)
        {
            // Save each file in the folder
            foreach (var formFile in submission.Files)
            {
                // Create the filepath for this file
                var filePath = Path.Combine(Directory.GetCurrentDirectory(), _rootStorageDirectory, 
                    submission.SubmissionId.ToString(), formFile.FileName);

                // Create any necessary folders for this filepath
                Directory.CreateDirectory(filePath);

                // Remove the folder created that is just the file name
                Directory.Delete(filePath);

                // Actually save the file, if there is anything to save
                if (formFile.Length > 0)
                {
                    using (var stream = new FileStream(filePath, FileMode.Create))
                    {
                        await formFile.CopyToAsync(stream);
                    }
                }
            }
        }
    }
}