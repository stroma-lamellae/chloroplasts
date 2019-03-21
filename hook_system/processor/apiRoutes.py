import os
# from submission import Submission
from hookFile import HookFile
from hookFileType import HookFileType
import submissionQueue
from datetime import datetime, timedelta
import uuid
import tarfile as tar
from tempfile import SpooledTemporaryFile

validFileExt = {'.java', '.cpp', '.c', '.hpp', '.h'}

def submit(userId: str, email: str, data) -> str:

    #TODO auth stuff before anything continues
    # if not auth:
    #     return "Forbidden", 403

    jobID: str = str(uuid.uuid4())
    filename: str = "./Queue/"+jobID+".tar.gz"

    with open(filename, 'wb') as f:
        for line in data.stream:
            f.write(line)

    with tar.open(fileobj=data.stream, mode='r') as tarFile:
        for fileName in tarFile.getnames():
            if tarFile.getmember(fileName).isfile() :

                #Break up the file path into it's respective folders
                filePathElements: List[str] = os.path.normpath(fileName).split(os.sep)

                if len(filePathElements) != 2 and len(filePathElements) != 3:
                    return "Unrecognized Folder Structure", 400

                ext = fileName[fileName.rfind('.'):]

                if ext not in validFileExt:
                    return "Invalid File Type: " + ext, 400

                if filePathElements[0] == "PreviousYears" or filePathElements[0] == "CurrentYear":
                    if len(filePathElements[1].split('_')) != 3:
                        return "Invalid Student Folder", 400
                elif filePathElements[0] != "Exclusions":
                    return "Unrecognized Data Category", 400

    added, waitTime = submissionQueue.addToQueue(filename, email)

    if added:
        return {"JobId" : jobID, "EstimatedCompletion" : datetime.now() + timedelta(minutes=5)}
    else:
        return "Unable to Add Submission to Queue", 400

def fetch(userId: str, jobId: str) -> str:

    #TODO auth stuff before anything continues
    # if not auth:
    #     return "Forbidden", 403

    # TODO this will be read from config file
    resultPath = os.path.join("./Results", jobId + ".xml")

    if not os.path.exists(resultPath):
        return {'results': '<?xml version="1.0" encoding="UTF-8" ?><Results></Results>'}

    xmlResults = ""

    with open(resultPath, 'r') as f:
        xmlResults = ''.join(f.readlines())

    os.remove(resultPath)

    return {'results': xmlResults}