#!/usr/bin/python3
import ctypes
import sys
import os
import psycopg2

from os import listdir

folder = sys.argv[1]

destinationFolder = 'C:\\Users\\Emilia\\Documents\\ScrubbedData' #can be read from the datababase, initialized to the professors home directory
os.mkdir(destinationFolder)

unScrubbedFolders = ""
numOfUnscrubbedFolders = 0
try:
    conn = psycopg2.connect(host="localhost", database="clientserver", user="clientserver", password="password")
    cur = conn.cursor()
except:
    print("error connecting to the database")

for section in listdir(folder):
    os.mkdir(destinationFolder+"\\"+section)
    if section == "Current Year" or section == "Previous Years":
        for studentSubmission in listdir(folder+"\\"+section):
            try:
                firstName, lastName, stdNum = studentSubmission.split("-")
                hashFirstName = str(hash(firstName))
                hashLastName = str(hash(lastName))
                hashStdNum = str(hash(stdNum))
                scrubbedStudentFolder = destinationFolder+"\\"+section+"\\"+hashFirstName+"-"+hashLastName+"-"+hashStdNum)
                os.mkdir(scrubbedStudentFolder)
                # save hash in the database HERE
                cur.execute("INSERT INTO StudentHashMapping SET Hash_Firstname = "+hashFirstName+" Hash_Lastname = "+hashLastName+" HashStudentNumber = " + hashStdNum + "Firstname = "+FirstName+" Lastname = "+LastName+" StudentNumber = " + StdNum)

                for filename in listdir(folder+"\\"+section+"\\"+studentSubmission):
                    if filename.endswith(".java") or filename.endswith(".cpp") or filename.endswith(".c") or filename.endswith(".hpp") or filename.endswith(".h"):
                        #scrub data
                        f = open(folder+"\\"+section+"\\"+studentSubmission+"\\"+filename).read()
                        replace = f.replace(firstName, str(hash(firstName))).replace(lastName, str(hash(lastName))).replace(stdNum, str(hash(stdNum)))
                        newF = open(scrubbedStudentFolder+"\\Scrubbed-"+filename, 'w')
                        newF.write(replace)
                        newF.close()
            except:
                #this code will be executed if the folder is not named properly
                unScrubbedFolders = "\t" + studentSubmission + "\n"
                numOfUnscrubbedFolders = numOfUnscrubbedFolders + 1

#if any folder causes an exception, then show an alert at the end with the summary
if numOfUnscrubbedFolders == 1:
    alertMessage = "A submission were not able to be scrubbed. It is listed below:\n"
    alertMessage = alertMessage + unScrubbedFolders
    ctypes.windll.user32.MessageBoxW(0, alertMessage, "Alert", 1)
elif numOfUnscrubbedFolders > 1:
    alertMessage = str(numOfUnscrubbedFolders)+" submissions were not able to be scrubbed. They are listed below:\n"
    alertMessage = alertMessage + unScrubbedFolders
    ctypes.windll.user32.MessageBoxW(0, alertMessage, "Alert", 1)

if conn is not None:
    conn.close()