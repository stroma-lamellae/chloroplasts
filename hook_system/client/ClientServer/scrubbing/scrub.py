#!/usr/bin/python3
import sys
import os
import psycopg2

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
    mainDestinationFolder = join(destinationFolder, section)
    os.mkdir(mainDestinationFolder)
    if section == "Exclusions":
        for root, directory, files in os.walk(join(folder, section)):
            for filename in files:
                if filename.endswith(".java") or filename.endswith(".cpp") or filename.endswith(".c") \
                        or filename.endswith(".hpp") or filename.endswith(".h"):
                    origFile = open(join(root, filename)).read()
                    # write to scrubbed folder
                    newFile = join(mainDestinationFolder, filename)
                    newF = open(newFile, 'w')
                    newF.write(origFile)
                    newF.close()
    if section == "CurrentYear" or section == "PreviousYears":
        for studentSubmission in listdir(join(folder, section)):
            try:
                #take note of each folder you are going into
                studentSubmissionFolder = join(join(folder, section), studentSubmission)

                #get the names in plain english, and save them to variables
                firstName, lastName, stdNum, subId = studentSubmission.split("_")

                #save the hash values of the 3 variables from above
                hashFirstName = str(hash(firstName))
                hashLastName = str(hash(lastName))
                hashStdNum = str(hash(stdNum))

                #create directory to save the scrubbed data to
                scrubbedStudentFolder = join(join(destinationFolder, section), hashFirstName+"_"+hashLastName+"_"+subId)

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
                for root, directory, files in os.walk(studentSubmissionFolder):
                    for filename in files:
                        if filename.endswith(".java") or filename.endswith(".cpp") or filename.endswith(".c") \
                                or filename.endswith(".hpp") or filename.endswith(".h"):
                            #scrub data
                            f = open(join(root, filename)).read()
                            replace = f.replace(firstName, hashFirstName).replace(lastName, hashLastName)\
                                .replace(stdNum, hashStdNum)
                            #write to scrubbed file
                            betweenPath = root.replace(studentSubmissionFolder + os.path.sep, '')
                            os.makedirs(join(scrubbedStudentFolder, betweenPath))
                            newFolder = join(scrubbedStudentFolder, betweenPath, filename)
                            newF = open(newFolder, 'w')
                            newF.write(replace)
                            newF.close()
            except:
                unScrubbedFolders = "\t" + studentSubmission + "\n"
                numOfUnscrubbedFolders = numOfUnscrubbedFolders + 1

#if any folder causes an exception, send a sys.exit error message
if numOfUnscrubbedFolders == 1:
    alertMessage = "A submission was not able to be scrubbed. It is listed below:\n"
    alertMessage = alertMessage + unScrubbedFolders
    sys.exit(alertMessage)
elif numOfUnscrubbedFolders > 1:
    alertMessage = str(numOfUnscrubbedFolders)+" submissions were not able to be scrubbed. They are listed below:\n"
    alertMessage = alertMessage + unScrubbedFolders
    sys.exit(alertMessage)

conn.commit()

#close the database connection
if conn is not None:
    conn.close()

#completed successfully
sys.exit(None)
