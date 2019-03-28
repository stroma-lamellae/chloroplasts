from hookFile import HookFile
from hookFileType import HookFileType
from datetime import datetime, timedelta
from tempfile import SpooledTemporaryFile
import uuid
import os
import tarfile as tar
import submissionQueue

validFileExt = {'.java', '.cpp', '.c', '.hpp', '.h'}

def submit(userId: str, email: str, data) -> str:

    #TODO auth stuff before anything continues
    # if not auth:
    #     return "Forbidden", 403
    
    with tar.open(fileobj=data.stream, mode='r') as tarFile:
        for fileName in tarFile.getnames():
            if tarFile.getmember(fileName).isfile() :

                #Break up the file path into it's respective folders
                filePathElements: List[str] = os.path.normpath(fileName).split(os.sep)

                #Checking to make sure each file is either 1 folder deep or 2 folders deep
                if len(filePathElements) != 2 and len(filePathElements) != 3:
                    return "Unrecognized Folder Structure", 400

                ext = fileName[fileName.rfind('.'):]

                #If a file is sent that is not supported report it
                if ext not in validFileExt:
                    return "Invalid File Type: " + ext, 400

                #Verifying the folder structure of each file
                if filePathElements[0] == "PreviousYears" or filePathElements[0] == "CurrentYear":
                    if len(filePathElements[1].split('_')) != 3:
                        return "Invalid Student Folder", 400
                elif filePathElements[0] != "Exclusions":
                    return "Unrecognized Data Category", 400

    #Create a 128 bit job number represented in a hex string
    jobID: str = str(uuid.uuid4())

    #Write the tarball to disk to be processed later
    filename: str = "./Queue/"+jobID+".tar.gz"
    with open(filename, 'wb') as f:
        data.stream.seek(0) # Needed because we read already read the tarball once
        for line in data.stream:
            f.write(line)

    #Add the filename to a queue to process
    added, waitTime = submissionQueue.addToQueue(filename, email)

    if added:
        return {"JobId" : jobID, "EstimatedCompletion" : waitTime}
    else:
        return "Unable to Add Submission to Queue", 400

def fetch(userId: str, jobId: str) -> str:

    #TODO auth stuff before anything continues
    # if not auth:
    #     return "Forbidden", 403

    # TODO this will be read from config file
    resultPath = os.path.join("./Results", jobId + ".xml")

    #If the results don't exist return empty results
    if not os.path.exists(resultPath):
        return {'results': '<?xml version="1.0" encoding="UTF-8" ?><Results></Results>'}

    #Read the results and send them back to the client server
    xmlResults = ""
    with open(resultPath, 'r') as f:
        xmlResults = ''.join(f.readlines())

    os.remove(resultPath)

    return {'results': xmlResults}