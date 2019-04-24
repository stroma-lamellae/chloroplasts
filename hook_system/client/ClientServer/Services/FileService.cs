using System;
using ClientServer.Models;
using Microsoft.AspNetCore.Http;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using SharpCompress.Common;
using SharpCompress.Readers;
using SharpCompress.Writers;

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

        // ignore: When true, ignores non-code files
        void CopyAssignment(Assignment assignment, string dest, bool ignore = false);

        // Deletes everything within a directory
        void EmptyDirectory(string directory);

        // Returns the root storage directory
        string GetStorageDirectory();

        // Creates a tarball at the "dest" location from the files in 
        // the "source" directory. 
        void CompressFolder(string source, string dest);

        // Extracts the given file (assuming it is compressed) to a temporary
        //  folder and returns the location of that temporary folder
        string ExtractFile(IFormFile file);

        // Saves the files in this submission object.
        // The submission needs a valid SubmissionId, as well as the Assignment and Course loaded
        void PersistSubmissionFiles(Submission submission, string sourceDirBase);

        // Saves the files, except it is expecting a custom folder name
        // Mainly used for the test submission
        void PersistSubmissionFiles(Submission submission, string sourceDirBase, string foldername);

        // Reads a code file from the Temp/Scrubbed/{filePath} location
        // and returns an array of read lines
        Task<FileResult> ReadFileFromStorageAsync(long submissionId, string lineFilePath, string submissionFilePath);
    }

    public class FileService : IFileService
    {
        private const string RootStorageDirectory = "Temp";

        private readonly string[] _allowedExtensions = new string[] {".java", ".c", ".cpp", ".h", ".hpp"};

        // Dest is the path relative to the global root storage directory
        //  So far whatever dest you pass in, it will prepend the root storage directory
        public void CopyAssignment(Assignment assignment, string dest, bool ignore = false)
        {
            var destPath = Path.Combine(Directory.GetCurrentDirectory(), RootStorageDirectory, dest);
            foreach (var submission in assignment.Submissions)
            {
                var submissionPath = Path.Combine(Directory.GetCurrentDirectory(), RootStorageDirectory, submission.FilePath);
                var subFolderName = GetSubmissionFolderName(submission);
                if (!ignore) subFolderName = $"{subFolderName}_{submission.SubmissionId}";
                var submissionDest = Path.Combine(destPath, subFolderName);
                DirectoryCopy(submissionPath, submissionDest, true, ignore);
            }
        }

        // Saves the files in this submission object.
        // The submission needs a valid SubmissionId, as well as the Assignment and Course loaded
        public void PersistSubmissionFiles(Submission submission)
        {
            var submissionPath = GetSubmissionPath(submission);
            var basePath = Path.Combine(Directory.GetCurrentDirectory(), RootStorageDirectory, submissionPath);
            submission.FilePath = submissionPath;
                
            // Save each file in the folder
            if (submission.Files != null) {
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
                            formFile.CopyTo(stream);
                        }
                    }
                }
            }
        }
        // Saves the files in this submission object.
        // The submission needs a valid SubmissionId, as well as the Assignment and Course loaded
        public void PersistSubmissionFiles(Submission submission, string sourceDirBase)
        {
            var submissionPath = GetSubmissionPath(submission);
            var destPath = Path.Combine(Directory.GetCurrentDirectory(), RootStorageDirectory, submissionPath);
            submission.FilePath = submissionPath;
            // var sourcePath = sourceDirBase + Path.DirectorySeparatorChar + GetSubmissionFolderName(submission);
            var sourcePath = Path.Combine(sourceDirBase, GetSubmissionFolderName(submission));
            DirectoryCopy(sourcePath, destPath, true);
        }

        // Saves the files, except it is expecting a custom folder name
        // Mainly used for the test submission
        public void PersistSubmissionFiles(Submission submission, string sourceDirBase, string foldername)
        {
            var submissionPath = GetSubmissionPath(submission);
            var destPath = Path.Combine(Directory.GetCurrentDirectory(), RootStorageDirectory, submissionPath);
            submission.FilePath = submissionPath;
            var sourcePath = Path.Combine(sourceDirBase, foldername);
            DirectoryCopy(sourcePath, destPath, true);
        }

        // https://stackoverflow.com/questions/1288718/how-to-delete-all-files-and-folders-in-a-directory
        public void EmptyDirectory(string directory)
        {
            var directoryLoc = Path.Combine(Directory.GetCurrentDirectory(), RootStorageDirectory, directory);
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
            return Path.Combine($"{submission.Assignment.Course.Year}", submission.Assignment.Course.ProgramCode, 
                submission.Assignment.Course.CourseCode, submission.Assignment.Name, $"{submission.SubmissionId}",
                GetSubmissionFolderName(submission));
        }

        private string GetSubmissionFolderName(Submission submission)
        {
            return submission.StudentFirstname + "_" + submission.StudentLastname + "_" + submission.StudentNumber;
        }

        // https://docs.microsoft.com/en-us/dotnet/standard/io/how-to-copy-directories
        private void DirectoryCopy(string sourceDirName, string destDirName, bool copySubDirs, bool ignore = false)
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
                if (ignore) {
                    var extension = Path.GetExtension(file.FullName);
                    bool valid = false;
                    foreach (string item in _allowedExtensions) {
                        if (extension.Equals(item)) {
                            valid = true;
                            break;
                        }
                    }
                    if (!valid) continue;
                }
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

        public void CompressFolder(string source, string dest)
        {
            var sourcePath = Path.Combine(RootStorageDirectory, source);
            var destPath = Path.Combine(RootStorageDirectory, dest);

            var options = new WriterOptions(CompressionType.GZip);
            options.LeaveStreamOpen = true;

            using (Stream stream = File.OpenWrite(destPath))
            using (var writer = WriterFactory.Open(stream, ArchiveType.Tar, options))
                                                
            {
                writer.WriteAll(sourcePath, "*", SearchOption.AllDirectories);   
            }
        }

        public string ExtractFile(IFormFile file)
        {
            string filePath = Path.Combine(Path.GetTempPath(), Path.GetTempFileName().Split(".")[0]);
            using (Stream stream = file.OpenReadStream())
            using (var reader = ReaderFactory.Open(stream))
            {
                while (reader.MoveToNextEntry())
                {
                    if (!reader.Entry.IsDirectory)
                    {
                        reader.WriteEntryToDirectory(filePath, new ExtractionOptions()
                        {
                            ExtractFullPath = true,
                            Overwrite = true
                        });
                    }
                }
            }
            return filePath;
        }

        public async Task<FileResult> ReadFileFromStorageAsync(long submissionId, string lineFilePath, string submissionFilePath)
        {
            var filename = lineFilePath;
            // Handle scrubbed data
            if (filename.StartsWith("Scrubbed-")) {
                filename = filename.Substring(filename.IndexOf('-') + 1);
            }
            var path = Path.Join("Temp", submissionFilePath, filename);
            
            var lines = await System.IO.File.ReadAllLinesAsync(path);
            
            return new FileResult()
            {
                filePath = lineFilePath,
                lines = lines,
                submissionId = submissionId,
                fileName = filename
            };
        }
        
        public string GetStorageDirectory() 
        {
            return RootStorageDirectory;
        }
    }

    public class FileResult
    {
        public long submissionId { get; set; }
        public string[] lines { get; set; }
        public string filePath { get; set; }
        public string fileName { get; set; }
    }
}