import tarfile as tar
import os
from submission import Submission
from hookFile import HookFile
from hookFileType import HookFileType
import processSubmissions
from datetime import datetime, timedelta
import uuid

def submit(userId: str, email: str, data) -> str:

    #TODO auth stuff before anything continues
    # if not auth:
    #     return "Forbidden", 403

    jobID: str = str(uuid.uuid4())
    filename: str = "./Queue/"+jobID+".tar.gz"

    with open(filename, 'w') as f:
        f.write(data.stream)


    #MOVE THIS STUFF TO PROCESS FUNCTION
    # submission = Submission(email)

    # with tar.open(fileobj=data.stream, mode='r') as tarFile:
    #     for fileName in tarFile.getnames():
    #         if tarFile.getmember(fileName).isfile() :

    #             category, student, _ = fileName.split('/')

                
    #             ext = fileName[fileName.rfind('.'):]

    #             fType = None
    #             if ext == ".java":
    #                 fType = HookFileType.JAVA
    #             elif ext == ".cpp" or ext == ".c" or ext == ".hpp" or ext == ".h":
    #                 fType = HookFileType.C
    #             else:
    #                 return "Unrecognized File Type", 400

    #             # TODO Need to consult with the client team on how they'll have it stored on their end and how the want to receive the filename
    #             # but for now we're just going to keep it to the entire path from the tarball
    #             hFile = HookFile(fileName, student, fType, tarFile.extractfile(fileName).read().decode('utf-8'))

    #             if category == "Previous Years":
    #                 submission.previousYear.append(hFile)
    #             elif category == "Current Year":
    #                 submission.currentYear.append(hFile)
    #             elif category == "Exclusions":
    #                 submission.excludedWork.append(hFile)
    #             else:
    #                 return "Unrecognized Data Category", 400

    added, waitTime = processSubmissions.addToQueue(filename, email)

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
        xmlResults = f.readlines().join('')

    os.remove(resultPath)

    return xmlResults