from hookFile import HookFile
from hookFileType import HookFileType
from typing import List
import re
import submissionQueue
import connexion
import arrow
import bcrypt
import uuid
import os
import tarfile as tar
import psycopg2
import configparser

dir_path = os.path.dirname(os.path.realpath(__file__))
configFilename = os.path.join(dir_path,"config.ini")

config = configparser.RawConfigParser()
config.read(configFilename)

validFileExt = {'.java', '.cpp', '.c', '.hpp', '.h'}

def submit(userId: str, email: str, data) -> str:

    auth_ok = authorize(userId)
    if not auth_ok[0]:
        return auth_ok[1],auth_ok[2]

    #Create a 128 bit job number represented in a hex string
    jobID: str = str(uuid.uuid4())

    #Write the tarball to disk to be processed later
    filename: str = os.path.join(config["DISK"]["Queue"], "Queue", jobID + ".tar.gz")
    with open(filename, 'wb') as f:
        for line in data.stream:
            f.write(line)

    fileCount = 0
    java_files = 0
    cpp_files = 0
    with tar.open(filename, mode='r') as tarFile:
        for fileName in tarFile.getnames():
            if tarFile.getmember(fileName).isfile():

                #Break up the file path into it's respective folders
                filePathElements: List[str] = os.path.normpath(fileName).split(os.sep)

                #Checking to make sure each file is either 1 folder deep or 2 folders deep
                if len(filePathElements) < 2 :
                    os.remove(filename)
                    return "Unrecognized Folder Structure", 400

                ext = fileName[fileName.rfind('.'):]

                #If a file is sent that is not supported report it
                if ext not in validFileExt:
                    os.remove(filename)
                    return "Invalid File Type: " + ext, 400

                if filePathElements[0] == "CurrentYear" and ext in validFileExt:
                    if ext != ".java":
                        cpp_files+=1
                    else:
                        java_files+=1

                #Verifying the folder structure of each file
                if filePathElements[0] == "PreviousYears" or filePathElements[0] == "CurrentYear":
                    if len(filePathElements[1].split('_')) != 3:
                        os.remove(filename)
                        return "Invalid Student Folder", 400
                elif filePathElements[0] != "Exclusions":
                    os.remove(filename)
                    return "Unrecognized Data Category", 400

                fileCount+=1
    if java_files < 1 and cpp_files < 1:
        os.remove(filename)
        return "Insufficient files to detect plagiarism", 400

    #Add the filename to a queue to process
    added, waitTime = submissionQueue.addToQueue(filename,fileCount, email)
    addJob(userId, jobID)

    if added:
        return {"JobId" : jobID, "EstimatedCompletion" : waitTime}
    else:
        return "Unable to Add Submission to Queue", 400

def fetch(userId: str, jobId: str) -> str:
    auth_ok = authorize(userId)
    if not auth_ok[0]:
        return auth_ok[1],auth_ok[2]

    #Check if valid job id
    pattern = re.compile("[0-9a-fA-F]{8}\-[0-9a-fA-F]{4}\-[0-9a-fA-F]{4}\-[0-9a-fA-F]{4}\-[0-9a-fA-F]{12}")
    if not pattern.match(jobId):
        return ("Forbidden",403)

    #Check if JobID belongs to user
    if not checkForOwnership(userId, jobId):
        return ("Forbidden",403)

    resultPath = os.path.join(config["DISK"]["RESULT"], "Results", jobId + ".xml")

    #If the results don't exist yet return empty results
    if not os.path.exists(resultPath):
        return {'results': '<results />', 'status': 'queued', 'wait': submissionQueue.estimateQueue(jobId)}

    #Read the results and send them back to the client server
    xmlResults = ""
    with open(resultPath, 'r') as f:
        xmlResults = ''.join(f.readlines())

    os.remove(resultPath)
    removeJob(jobId)

    return {'results': xmlResults, 'status': 'complete', 'wait':''}

def checkForOwnership(userId: str, jobId: str) ->  bool:
    try:
        conn = psycopg2.connect(host="localhost", database=config["DATABASE"]["DATABASE_NAME"],user=config["DATABASE"]["DATABASE_USER"],password=config["DATABASE"]["DATABASE_PASSWORD"])
        cur = conn.cursor()
        selectJob = "SELECT job_id FROM jobs WHERE job_id = %s AND user_id = %s"
        cur.execute(selectJob, (jobId, userId, ))
        dbVal = cur.fetchone()
        if dbVal:
            if jobId == dbVal[0]:
                return True
            else:
                return False
        else:
            False
    except:
        return False

def addJob(userId: str, jobId: str):
    try:
        conn = psycopg2.connect(host="localhost", database=config["DATABASE"]["DATABASE_NAME"],user=config["DATABASE"]["DATABASE_USER"],password=config["DATABASE"]["DATABASE_PASSWORD"])
        cur = conn.cursor()
        mkJob = "INSERT INTO jobs (job_id, user_id) VALUES (%s, %s);"
        cur.execute(mkJob, (jobId, userId, ))
        conn.commit()
    except:
        pass

def removeJob(jobId: str):
    try:
        conn = psycopg2.connect(host="localhost", database=config["DATABASE"]["DATABASE_NAME"],user=config["DATABASE"]["DATABASE_USER"],password=config["DATABASE"]["DATABASE_PASSWORD"])
        cur = conn.cursor()
        rmJob = "DELETE FROM jobs WHERE job_id = %s;"
        cur.execute(rmJob, (jobId, ))
        conn.commit()
    except:
        pass

def authorize(userId) -> (bool,int,str):
    licence = connexion.request.headers['licence']
    try:
        conn = psycopg2.connect(host="localhost", database=config["DATABASE"]["DATABASE_NAME"],user=config["DATABASE"]["DATABASE_USER"],password=config["DATABASE"]["DATABASE_PASSWORD"])
        cur = conn.cursor()
        select_licence = "SELECT licence_number, user_name FROM accounts WHERE user_id = %s;"
        cur.execute(select_licence, (userId, ))
        db_values = cur.fetchone()
        if db_values:
            if bcrypt.hashpw(bytes(licence, "utf-8"), bytes(db_values[0],"utf-8")) == bytes(db_values[0],"utf-8"):
                return(True, ("Authorized Licence for user: %s", db_values[1]), 200)
            else:
                return (False, "Forbidden", 403)
        else:
            return (False,"Forbidden",403)
    except:
        #will stop execution and send back the error message
        #sys.exit("error connecting to the database")
        return (False,"Error connecting to database", 400)

