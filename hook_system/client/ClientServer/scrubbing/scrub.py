#!/usr/bin/python3
import sys
import os
import psycopg2
import tkinter as tk

from tkinter import messagebox
from os import listdir
from os.path import join

folder = sys.argv[1]
destinationFolder = sys.argv[2]
dbUsername = sys.argv[3]
dbPassword = sys.argv[4]

try:
    conn = psycopg2.connect(host="localhost", database="clientserver", user=dbUsername, password=dbPassword)
    cur = conn.cursor()
except:
    #will stop execution and send back the error message
    sys.exit("error connecting to the database")

#destinationFolder is being passed as a parameter for now
if not os.path.exists(destinationFolder):
    os.mkdir(destinationFolder)

unScrubbedFolders = ""
numOfUnscrubbedFolders = 0

for section in listdir(folder):
    os.mkdir(join(destinationFolder, section))
    if section == "Current Year" or section == "Previous Years":
        for studentSubmission in listdir(join(folder, section)):
            try:
                #take not of each folder you are going into
                studentSubmissionFolder = join(join(folder, section), studentSubmission)

                #get the names in plain english, and save them to variables
                firstName, lastName, stdNum = studentSubmission.split("_")

                #save the hash vaules of the 3 variables from above
                hashFirstName = str(hash(firstName))
                hashLastName = str(hash(lastName))
                hashStdNum = str(hash(stdNum))

                #create directory to save the scrubbed data to
                scrubbedStudentFolder = join(join(destinationFolder, section), hashFirstName+"_"+hashLastName+"_"+hashStdNum)

                #Create the folder so the files have somewhere to go
                os.mkdir(scrubbedStudentFolder)

                # save hash in the database HERE
                try:
                    cur.execute("INSERT INTO \"StudentHashMapping\" (\"Hash_Firstname\", \"Hash_Lastname\", " +
                                "\"Hash_StudentNumber\", \"Firstname\", \"Lastname\", \"StudentNumber\") VALUES " +
                                "(%s, %s, %s, %s, %s, %s);", (hashFirstName, hashLastName, hashStdNum, firstName, lastName, str(stdNum)))
                except:
                    #does not exit the program, we want to process all the student submissions that we can
                    sys.exit("Unable to insert into database")

                #Loop through each file in the student submission folder and replace identifying info
                for filename in listdir(studentSubmissionFolder):
                    if filename.endswith(".java") or filename.endswith(".cpp") or filename.endswith(".c") \
                            or filename.endswith(".hpp") or filename.endswith(".h"):
                        #scrub data
                        f = open(join(studentSubmissionFolder, filename)).read()
                        replace = f.replace(firstName, hashFirstName).replace(lastName, hashLastName)\
                            .replace(stdNum, hashStdNum)
                        #write to scrubbed file
                        newFolder = join(scrubbedStudentFolder, "Scrubbed-"+filename)
                        newF = open(newFolder, 'w')
                        newF.write(replace)
                        newF.close()
            except:
                #this code will be executed if the folder is not named properly
                unScrubbedFolders = "\t" + studentSubmission + "\n"
                numOfUnscrubbedFolders = numOfUnscrubbedFolders + 1

#if any folder causes an exception, then show an alert at the end with the summary
if numOfUnscrubbedFolders == 1:
    alertMessage = "A submission was not able to be scrubbed. It is listed below:\n"
    alertMessage = alertMessage + unScrubbedFolders
    root = tk.Tk()
    root.withdraw()
    messagebox.showwarning('ALERT', alertMessage)
elif numOfUnscrubbedFolders > 1:
    alertMessage = str(numOfUnscrubbedFolders)+" submissions were not able to be scrubbed. They are listed below:\n"
    alertMessage = alertMessage + unScrubbedFolders
    root = tk.Tk()
    root.withdraw()
    messagebox.showwarning('ALERT', alertMessage)

conn.commit()

#close the database connection
if conn is not None:
    conn.close()

#completed successfully
sys.exit(None)