using ClientServer.Models;
using System.IO;
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Microsoft.Extensions.Configuration;
/*
This calls the scrubbing script
*/

namespace ClientServer.Services
{
    public interface IScrubbingService
    {
        string ScrubPackage(Package package);
    }

    public class ScrubbingService: IScrubbingService
    {
        private readonly string _preScrubDirectory = "PreScrub";
        private readonly string _postScrubDirectory = "Scrubbed";
        private readonly string _currentAssignmentDirectory = "Current Year";
        private readonly string _previousAssignmentsDirectory = "Previous Years";
        private readonly IFileService _fileService;
        private readonly IConfiguration _configuration;

        public ScrubbingService(IFileService fileService, IConfiguration configuration)
        {
            _fileService = fileService;
            _configuration = configuration;
        }

        public string ScrubPackage(Package package)
        {
            // Clear the scrub folders
            _fileService.EmptyDirectory(_preScrubDirectory);
            _fileService.EmptyDirectory(_postScrubDirectory);
            
             // Copy all files into the scrub folder location
             // Copy the current assignment
            var currAssignmentPath = Path.Combine(_preScrubDirectory, _currentAssignmentDirectory);
            _fileService.CopyAssignment(package.Assignment, currAssignmentPath);

            // Copy the previous assignments
            var prevAssignmentsPath = Path.Combine(_preScrubDirectory, _previousAssignmentsDirectory);
            foreach (var prevAssignment in package.PreviousAssignments)
            {
                _fileService.CopyAssignment(prevAssignment.Assignment, prevAssignmentsPath);
            }

            RunScript();

            string destPath = Path.Combine(Path.GetTempPath(), Path.GetTempFileName() + ".tar.gz");

            // Tar the file
            _fileService.CompressFolder(_postScrubDirectory, destPath);

            return destPath;
        }

        // Actually runs the scrubbing script
        private void RunScript() 
        {
            // Run the python script by creating a shell, and piping commands through stdin
            string shellString;
            string activateString;
            string scriptLocation = Path.Combine("scrubbing", "scrub.py");
            string storageDirectory = _fileService.GetStorageDirectory();
            string preScrubLoc = Path.Combine(storageDirectory, _preScrubDirectory);
            string postScrubLoc = Path.Combine(storageDirectory, _postScrubDirectory);
            string connectionString = _configuration.GetConnectionString("ClientServerDatabase");
            string username = connectionString.Split(';')[3].Replace("Username=", "");
            string password = connectionString.Split(';')[4].Replace("Password=", "");

            // OS specific information. Need different way to activate env, and different shell commands
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux) || RuntimeInformation.IsOSPlatform(OSPlatform.OSX)) {  
                shellString = "/bin/bash";
                activateString = "source " + Path.Combine("scrubbing", "env", "bin", "activate");
            } else {
                shellString = "cmd.exe";
                activateString = Path.Combine("scrubbing", "env", "Scripts", "activate");
            }

            // Create the process, and make it run a shell / cmd
            Process p = new Process();
            ProcessStartInfo info = new ProcessStartInfo();
            info.FileName = shellString;
            info.RedirectStandardInput = true;
            info.UseShellExecute = false;

            p.StartInfo = info;
            p.Start();

            // Pipe commands into our shell
            using (StreamWriter sw = p.StandardInput)
            {
                if (sw.BaseStream.CanWrite)
                {
                    sw.WriteLine(activateString);
                    sw.WriteLine("python " + scriptLocation + " " + preScrubLoc + " " + postScrubLoc + " " + username + " " + password);
                }
            }
            p.WaitForExit();
            p.Close();
        }
    }
}