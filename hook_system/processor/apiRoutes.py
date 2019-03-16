import tarfile as tar
import os
from submission import Submission
from hookFile import HookFile
from hookFileType import HookFileType
from processSubmissions import ProcessSubmissions
from datetime import datetime, timedelta

def submit(userId: str, email: str, data) -> str:

    #TODO auth stuff before anything continues
    # if not auth:
    #     return "Forbidden", 403

    submission = Submission(email)

    with tar.open(fileobj=data.stream, mode='r') as tarFile:
        for fileName in tarFile.getnames():
            if tarFile.getmember(fileName).isfile() :

                category, student, _ = fileName.split('/')

                
                ext = fileName[fileName.rfind('.'):]

                fType = None
                if ext == ".java":
                    fType = HookFileType.JAVA
                elif ext == ".cpp" or ext == ".c" or ext == ".hpp" or ext == ".h":
                    fType = HookFileType.C
                else:
                    return "Unrecognized File Type", 400

                # TODO Need to consult with the client team on how they'll have it stored on their end and how the want to receive the filename
                # but for now we're just going to keep it to the entire path from the tarball
                hFile = HookFile(fileName, student, fType, tarFile.extractfile(fileName).read().decode('utf-8'))

                # TODO Need to verify with client team that these are the folder names being used in the tarball, for now just go with this
                if category == "Previous Years":
                    submission.previousYear.append(hFile)
                elif category == "Current Year":
                    submission.currentYear.append(hFile)
                elif category == "Exclusions":
                    submission.excludedWork.append(hFile)
                else:
                    return "Unrecognized Data Category", 400

    added, jobId, waitTime = ProcessSubmissions.addToQueue(submission)

    if added:
        return {"JobId" : jobId, "EstimatedCompletion" : datetime.now() + timedelta(minutes=5)}
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