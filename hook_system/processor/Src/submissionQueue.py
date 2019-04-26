# Copyright (C) 2019 Hook System Authors
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is furnished to do
# so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

from submission import Submission
from match import Match
from hookFile import HookFile
from hookFileType import HookFileType
from standardizedFile import StandardizedFile
from typing import List, Tuple
from email.message import EmailMessage
import smtplib
import tarfile as tar
import threading
import time
import arrow
import os
import standardize
import winnow
import xmlGenerator
import configparser

timeQueue = list()
java_processing_per_file = 0.205
c_processing_per_file = 15.62
mutex = threading.Lock()
submissionQueue: List[Tuple[str, str]] = []

dir_path = os.path.dirname(os.path.realpath(__file__))
configFilename = os.path.join(dir_path,"config.ini")

if not os.path.isfile(configFilename):
    print("No configuration file found. Please run Setup before running this.")
    exit(0)

config = configparser.RawConfigParser()
config.read(configFilename)


def addToQueue(filePath: str, numFile: int, java: bool, emailAddr: str) -> Tuple[bool, str]:

    mutex.acquire()

    nPrior: int = len(submissionQueue)

    submissionQueue.append((filePath, emailAddr))

    nCur:int = len(submissionQueue)

    if nCur == nPrior+1:
        estimate = estimateProcessing(numFile, java)
        timer = (filePath, arrow.utcnow(), estimate)
        timeQueue.append(timer)
        local_utc = arrow.utcnow().shift(seconds=estimate)

        mutex.release()
        return True, local_utc.to('local').format('YYYY-MM-DD HH:mm:ss')
    else:
        mutex.release()
        return False, ""

def processQueue():

    while True:
        emailAddr = "" # This is so we don't send an email to a previous person incase it fails before it pops off the queue
        try:
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
                num_files = 0
                start = time.time()
                with tar.open(filePath, mode='r') as tarFile:
                    for fileName in tarFile.getnames():
                        num_files+=1
                        if tarFile.getmember(fileName).isfile():

                            #Break up the file path into it's respective folders
                            filePathElements: List[str] = os.path.normpath(fileName).split(os.sep)
                            ext = fileName[fileName.rfind('.'):]

                            #This is a previous years submission so we need to use it to check for plagiarism but not actually
                            #check for plagiarism in this file
                            if filePathElements[0] == 'PreviousYears':
                                owner = filePathElements[1].split('_')[-1] #Get the student hash in the folder name

                                if ext == ".java": #If it's a java file then add it to the java list
                                    javaFiles.append(HookFile(fileName, owner, HookFileType.PREVIOUS_YEAR, tarFile.extractfile(fileName).read().decode('utf-8')))
                                elif ext == ".cpp" or ext == ".c" or ext == ".hpp" or ext == ".h": #If it's a C/C++ file add it to the C list
                                    cFiles.append(HookFile(fileName, owner, HookFileType.PREVIOUS_YEAR, tarFile.extractfile(fileName).read().decode('utf-8')))

                            # This is a current year submission so we need to actually check for plagiarism in it
                            elif filePathElements[0] == 'CurrentYear':
                                owner = filePathElements[1].split('_')[-1] #Get the student hash in the folder name

                                if ext == ".java":
                                    javaFiles.append(HookFile(fileName, owner, HookFileType.CURRENT_YEAR, tarFile.extractfile(fileName).read().decode('utf-8')))
                                elif ext == ".cpp" or ext == ".c" or ext == ".hpp" or ext == ".h":
                                    cFiles.append(HookFile(fileName, owner, HookFileType.CURRENT_YEAR, tarFile.extractfile(fileName).read().decode('utf-8')))

                            #This is a whitelist piece of code which shouldn't return plagiarism if it exists in a students submission
                            elif filePathElements[0] == 'Exclusions':
                                if ext == ".java":
                                    javaWhitelist.append(HookFile(fileName, "", None, tarFile.extractfile(fileName).read().decode('utf-8')))
                                elif ext == ".cpp" or ext == ".c" or ext == ".hpp" or ext == ".h":
                                    cWhitelist.append(HookFile(fileName, "", None, tarFile.extractfile(fileName).read().decode('utf-8')))
                """
                The MOSS paper on Winnowing goes into detail on how the winnowing algorithm work's and why it is necessary to standardize the input.
                Section 3 of the paper explains the winnowing algorithm while Section 5.2 describes how to use the algorithm for plagiarism detection.
                The Paper can be found at https://theory.stanford.edu/~aiken/publications/papers/sigmod03.pdf
                """

                #Standardize the files to be processed, this includes removing variable names.

                cStandardized: List[StandardizedFile] = standardize.standardizeC(cFiles)
                cStandardizedWhitelist : List[StandardizedFile] = standardize.standardizeC(cWhitelist)

                javaStandardized: List[StandardizedFile] = standardize.standardizeJava(javaFiles)
                javaStandardizedWhitelist : List[StandardizedFile] = standardize.standardizeJava(javaWhitelist)

                #Apply the winnowing algorithm to the standardized files
                cMatches: List[Match] = winnow.getMatches(cStandardized, cStandardizedWhitelist)
                javaMatches: List[Match] = winnow.getMatches(javaStandardized, javaStandardizedWhitelist, len(cMatches))

                _, tarFilename = os.path.split(filePath)

                jobId: str = tarFilename.replace('.tar.gz','')

                allMatches: List[Match] = cMatches
                allMatches += javaMatches
                with open(os.path.join(config["DISK"]["RESULT"], "Results", jobId + ".xml"), 'wb') as f:
                    f.write(xmlGenerator.generateResult(allMatches))
                processed_file = timeQueue.pop()
                os.remove(filePath)

                notified = __sendEmail(emailAddr,jobId)
                #not sure what the best thing to do here is. . .
                endtime = time.time()
                processing_per_file = (endtime-start)/num_files
                print("Overall processing time for "+processed_file[0]+" files is: "+ str(processing_per_file))
        except Exception as e:
            print(e)
            try: #Try to release it incase it hasn't been released
                mutex.release()
            except:
                pass

            try:
                msg = EmailMessage()
                msg.set_content("Error processing job with id: "+jobId+" please try submitting again.")
                msg["Subject"]= "Error With Job!"
                msg["To"] = emailAddr
                msg["From"] = config["EMAIL"]["FromAddr"]
                s = smtplib.SMTP_SSL(config["EMAIL"]["SMTP_Server"], config["EMAIL"]["SMTP_Port"])
                s.login(config["EMAIL"]["FromAddr"], config["EMAIL"]["FromPassword"])
                s.sendmail(config["EMAIL"]["FromAddr"], emailAddr, msg.as_string())
                s.quit()
            except:
                pass




def __sendEmail(emailAddr: str, jobId: str) -> bool:
    try:
        msg = EmailMessage()
        msg.set_content("Your results have been processed and are ready to be"+
        " downloaded from the hook. Please log in to your account and request"+
        " them with your user id and this job id: "+jobId)
        msg["Subject"]= "Your Results are Ready!"
        msg["To"] = emailAddr
        msg["From"] = config["EMAIL"]["FromAddr"]
        s = smtplib.SMTP_SSL(config["EMAIL"]["SMTP_Server"], config["EMAIL"]["SMTP_Port"])
        s.login(config["EMAIL"]["FromAddr"], config["EMAIL"]["FromPassword"])
        s.sendmail(config["EMAIL"]["FromAddr"], emailAddr, msg.as_string())
        s.quit()
    except Exception as e:
        print("Failed to send email notification")
        print(e)


def estimateQueue(jobId: str) -> int:
    mutex.acquire()

    res = 0

    for path, _, estimate in timeQueue:
        if path.find(jobId) == -1:
            res += estimate
        else:
            break

    mutex.release()
    local_utc = arrow.utcnow().shift(seconds=res)

    return local_utc.to('local').format('YYYY-MM-DD HH:mm:ss')

def estimateProcessing(numFile, java):

    wait_time = 0
    if timeQueue:
        for timer in timeQueue:
            wait_time+=timer[2]
    if java:
        return wait_time+(java_processing_per_file*numFile)
    else:
        return wait_time+(c_processing_per_file*numFile)

