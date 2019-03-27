from hookFile import HookFile
from hookFileType import HookFileType
import submissionQueue
import connexion
import arrow
import uuid
import os
import tarfile as tar
import psycopg2
from tempfile import SpooledTemporaryFile

validFileExt = {'.java', '.cpp', '.c', '.hpp', '.h'}

def submit(userId: str, email: str, data) -> str:

    auth_ok = authorize(userId)
    if not auth_ok[0]:
        return auth[2],auth[1]

    #Create a 128 bit job number represented in a hex string
    jobID: str = str(uuid.uuid4())

    #Write the tarball to disk to be processed later
    filename: str = "./Queue/"+jobID+".tar.gz"
    with open(filename, 'wb') as f:
        for line in data.stream:
            f.write(line)

    fileCount = 0
    with tar.open(filename, mode='r') as tarFile:
        for fileName in tarFile.getnames():
            if tarFile.getmember(fileName).isfile() :

                #Break up the file path into it's respective folders
                filePathElements: List[str] = os.path.normpath(fileName).split(os.sep)

                #Checking to make sure each file is either 1 folder deep or 2 folders deep
                if len(filePathElements) != 2 and len(filePathElements) != 3:
                    os.remove(filename)
                    return "Unrecognized Folder Structure", 400

                ext = fileName[fileName.rfind('.'):]

                #If a file is sent that is not supported report it
                if ext not in validFileExt:
                    os.remove(filename)
                    return "Invalid File Type: " + ext, 400

                #Verifying the folder structure of each file
                if filePathElements[0] == "PreviousYears" or filePathElements[0] == "CurrentYear":
                    if len(filePathElements[1].split('_')) != 3:
                        os.remove(filename)
                        return "Invalid Student Folder", 400
                elif filePathElements[0] == "Exclusions":
                    if len(filePathElements) != 2:
                        os.remove(filename)
                        return "Invalid Exclusion Structure", 400
                else:
                    os.remove(filename)
                    return "Unrecognized Data Category", 400

                fileCount+=1

    #Add the filename to a queue to process
    added, waitTime = submissionQueue.addToQueue(filename,fileCount, email)

    if added:
        return {"JobId" : jobID, "EstimatedCompletion" : waitTime}
    else:
        return "Unable to Add Submission to Queue", 400

def fetch(userId: str, jobId: str) -> str:
    auth_ok = authorize(userId)
    if not auth_ok[0]:
        return auth[2],auth[1]

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

def authorize(userId) -> (bool,int,str):
    licence = connexion.request.headers['{licence}']
    try:
        #need to look into secure way to store dbusername + password
        conn = psycopg2.connect(host="localhost", database="hookserver", user=dbUsername, password=dbPassword)
        cur = conn.cursor()
        select_user_id = "SELECT licence_number, user_id FROM accounts WHERE user_email = %s;"
        cur.execute(select_user_id, (email, ))
        db_values = cur.fetchone()
        if db_values:
            if bcrypt.hashpw(bytes(licence, "utf-8"), bytes(db_values[1], "utf-8")) == db_values[1]:
                print("Authorized Licence")
            if db_values[1] == userId:
                return (True,"User Authorized, Proceeding to Process",200)
        else:
            return (False,"Forbidden",403)
    except:
        #will stop execution and send back the error message
        #sys.exit("error connecting to the database")
        return (False,"Error connecting to database", 400)

