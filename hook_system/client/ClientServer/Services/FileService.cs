using ClientServer.Models;
using System.IO;

/*
This deals with anything to do with writing and saving files
 */

namespace ClientServer.Services
{
    public interface IFileService
    {
        // Saves the files in the submission object.
        // Used after the user uploads a submission
        void PersistSubmissionFiles(Submission submission);

        void CopyAssignment(Assignment assignment, string dest);

        // Deletes everything within a directory
        void EmptyDirectory(string directory);

        // Returns the root storage directory
        string GetStorageDirectory();
    }

    public class FileService : IFileService
    {
        private readonly string _rootStorageDirectory = "Temp";

        // Dest is the path relative to the global root storage directory
        //  So far whatever dest you pass in, it will prepend the root storage directory
        public void CopyAssignment(Assignment assignment, string dest)
        {
            var destPath = Path.Combine(Directory.GetCurrentDirectory(), _rootStorageDirectory, dest);
            foreach (var submission in assignment.Submissions)
            {
                var submissionPath = Path.Combine(Directory.GetCurrentDirectory(), _rootStorageDirectory, submission.FilePath);
                var submissionDest = Path.Combine(destPath, GetSubmissionFolderName(submission));
                DirectoryCopy(submissionPath, submissionDest, true);
            }
        }

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

        // https://stackoverflow.com/questions/1288718/how-to-delete-all-files-and-folders-in-a-directory
        public void EmptyDirectory(string directory)
        {
            var directoryLoc = Path.Combine(Directory.GetCurrentDirectory(), _rootStorageDirectory, directory);
            Directory.CreateDirectory(directoryLoc);
            DirectoryInfo di = new DirectoryInfo(directoryLoc);

            foreach (FileInfo file in di.GetFiles())
            {
                file.Delete(); 
            }
            foreach (DirectoryInfo dir in di.GetDirectories())
            {
                dir.Delete(true); 
            }
        }

        // Get's the path for where this submission's files should be stored
        private string GetSubmissionPath(Submission submission)
        {
            string orig = submission.Assignment.Course.CourseCode;
            int length = orig.Length;
            int half = length / 2;

            string courseCode = orig.Substring(0, half);
            if (half < 1) { // In case we, for some reason, have a Course.CourseCode of length 1
                courseCode = "z";
            } 
            string courseNumber = submission.Assignment.Course.CourseCode.Substring(half, length - half);

            return Path.Combine(submission.Assignment.Course.Year + "", courseCode, 
                courseNumber, submission.Assignment.Name, GetSubmissionFolderName(submission));
        }

        private string GetSubmissionFolderName(Submission submission)
        {
            return submission.StudentFirstname + "_" + submission.StudentLastname + "_" + submission.StudentNumber;
        }

        // https://docs.microsoft.com/en-us/dotnet/standard/io/how-to-copy-directories
        private void DirectoryCopy(string sourceDirName, string destDirName, bool copySubDirs)
        {
            // Get the subdirectories for the specified directory.
            DirectoryInfo dir = new DirectoryInfo(sourceDirName);

            if (!dir.Exists)
            {
                throw new DirectoryNotFoundException(
                    "Source directory does not exist or could not be found: "
                    + sourceDirName);
            }

            DirectoryInfo[] dirs = dir.GetDirectories();
            // If the destination directory doesn't exist, create it.
            if (!Directory.Exists(destDirName))
            {
                Directory.CreateDirectory(destDirName);
            }
            
            // Get the files in the directory and copy them to the new location.
            FileInfo[] files = dir.GetFiles();
            foreach (FileInfo file in files)
            {
                string temppath = Path.Combine(destDirName, file.Name);
                file.CopyTo(temppath, false);
            }

            // If copying subdirectories, copy them and their contents to new location.
            if (copySubDirs)
            {
                foreach (DirectoryInfo subdir in dirs)
                {
                    string temppath = Path.Combine(destDirName, subdir.Name);
                    DirectoryCopy(subdir.FullName, temppath, copySubDirs);
                }
            }
        }

        public string GetStorageDirectory() 
        {
            return _rootStorageDirectory;
        }
    }
}