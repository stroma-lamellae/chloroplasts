from submission import Submission
from match import Match
from hookFile import HookFile
from hookFileType import HookFileType
from standardizedFile import StandardizedFile
from typing import List, Tuple
import tarfile as tar
import threading
import time
import os
import standardize
import winnow
import xmlGenerator

mutex = threading.Lock()
submissionQueue: List[Tuple[str, str]] = []


def addToQueue(filePath: str, emailAddr: str) -> Tuple[bool, str]:
    
    
    mutex.acquire()

    nPrior: int = len(submissionQueue)

    submissionQueue.append((filePath, emailAddr))

    nCur:int = len(submissionQueue)

    mutex.release()

    if nCur == nPrior+1:
        return True, "10 Minutes" #TODO find a formula for wait time
    else:
        return False, ""



def processQueue():
    
    while True:
        mutex.acquire()

        #Queue is empty wait to check again
        if not submissionQueue:
            mutex.release()
            time.sleep(5)
        else:
            filePath, emailAddr = submissionQueue.pop(0)
            mutex.release()

            cFiles: List[HookFile] = []
            cWhitelist: List[HookFile] = []

            javaFiles: List[HookFile] = []
            javaWhitelist: List[HookFile] = []

            with tar.open(filePath, mode='r') as tarFile:
                for fileName in tarFile.getnames():
                    if tarFile.getmember(fileName).isfile():

                        #Break up the file path into it's respective folders
                        filePathElements: List[str] = os.path.normpath(fileName).split(os.sep)
                        
                        ext = fileName[fileName.rfind('.'):]

                        if filePathElements[0] == 'PreviousYears':
                            owner = filePathElements[1].split('_')[-1] #Get the student hash in the folder name

                            if ext == ".java":
                                javaFiles.append(HookFile(fileName, owner, HookFileType.PREVIOUS_YEAR, tarFile.extractfile(fileName).read().decode('utf-8')))
                            elif ext == ".cpp" or ext == ".c" or ext == ".hpp" or ext == ".h":
                                cFiles.append(HookFile(fileName, owner, HookFileType.PREVIOUS_YEAR, tarFile.extractfile(fileName).read().decode('utf-8')))

                        elif filePathElements[0] == 'CurrentYear':
                            owner = filePathElements[1].split('_')[-1] #Get the student hash in the folder name

                            if ext == ".java":
                                javaFiles.append(HookFile(fileName, owner, HookFileType.CURRENT_YEAR, tarFile.extractfile(fileName).read().decode('utf-8')))
                            elif ext == ".cpp" or ext == ".c" or ext == ".hpp" or ext == ".h":
                                cFiles.append(HookFile(fileName, owner, HookFileType.CURRENT_YEAR, tarFile.extractfile(fileName).read().decode('utf-8')))

                        elif filePathElements[0] == 'Exclusions':
                            if ext == ".java":
                                javaWhitelist.append(HookFile(fileName, "", None, tarFile.extractfile(fileName).read().decode('utf-8')))
                            elif ext == ".cpp" or ext == ".c" or ext == ".hpp" or ext == ".h":
                                cWhitelist.append(HookFile(fileName, "", None, tarFile.extractfile(fileName).read().decode('utf-8')))

            cStandardized: List[StandardizedFile] = standardize.standardizeC(cFiles)
            cStandardizedWhitelist : List[StandardizedFile] = standardize.standardizeC(cWhitelist)

            javaStandardized: List[StandardizedFile] = standardize.standardizeJava(javaFiles)
            javaStandardizedWhitelist : List[StandardizedFile] = standardize.standardizeJava(javaWhitelist)

            cMatches: List[Match] = winnow.getMatches(cStandardized, cStandardizedWhitelist)
            javaMatches: List[Match] = winnow.getMatches(javaStandardized, javaStandardizedWhitelist, len(cMatches))

            _, tarFilename = os.path.split(filePath)

            jobID: str = tarFilename.replace('.tar.gz','')

            allMatches: List[Match] = cMatches
            allMatches += javaMatches
            with open("./Results/"+jobID+".xml", 'wb') as f:
                f.write(xmlGenerator.generateResult(allMatches))

            os.remove(filePath)
                        
            #TODO SEND EMAIL 




def __sendEmail(emailAddr: str, msg: str) -> bool:
    return True
