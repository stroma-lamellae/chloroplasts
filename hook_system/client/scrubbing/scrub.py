#!/usr/bin/python3
import console
import sys
import os
from os import listdir

folder = sys.argv[1]

destinationFolder = 'C:\\Users\\Emilia\\Documents\\ScrubbedData' #can be read from the datababase, initialized to the professors home directory
os.mkdir(destinationFolder)

#The structure of the folder is Main -> Current , Previous, Whitelist - > student submit file **Get name and student number here** -> java file
#save hash in the database
#remember to hash both the current year and the previous year
#send an alert if any folder is unable to get scrubbed (filename is not scrubbed)

for section in listdir(folder):
    os.mkdir(destinationFolder+"\\"+section)
    if section == "Current Year" or section == "Previous Years":
        for studentSubmission in listdir(folder+"\\"+section):
            try:
                firstName, lastName, stdNum = studentSubmission.split("-")
                #save hash in the database HERE
                scrubbedStudentFolder = destinationFolder+"\\"+section+"\\"+str(hash(firstName))+"-"+str(hash(lastName))+"-"+str(hash(stdNum))
                os.mkdir(scrubbedStudentFolder)

                for filename in listdir(folder+"\\"+section+"\\"+studentSubmission):
                    if filename.endswith(".java") or filename.endswith(".cpp") or filename.endswith(".c") or filename.endswith(".hpp") or filename.endswith(".h"):
                        #scrub data
                        f = open(folder+"\\"+section+"\\"+studentSubmission+"\\"+filename).read()
                        replace = f.replace(firstName, str(hash(firstName))).replace(lastName, str(hash(lastName))).replace(stdNum, str(hash(stdNum)))
                        newF = open(scrubbedStudentFolder+"\\Scrubbed-"+filename, 'w')
                        newF.write(replace)
                        newF.close()
            except:
                #save data
                os.remove(destinationFolder)

#if any folder causes an exception, then show an alert at the end with the summary