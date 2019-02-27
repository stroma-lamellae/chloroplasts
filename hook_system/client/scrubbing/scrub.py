#!/usr/bin/python3
import sys
import os
from os import listdir

folder = sys.argv[1]

destinationFolder = 'C:\\Users\\Emilia\\Documents\\ScrubbedData' #can be read from the datababase, initialized to the professors home directory
os.mkdir(destinationFolder)

#The structure of the folder is Main -> Current , Previous, Whitelist - > student submit file **Get name and student number here** -> java file
#save hash in the database
#remember to hash both the current year and the previous year

for studentSubmission in listdir(folder):
    firstName, lastName, stdNum = studentSubmission.split("-")
    # print("First Name: " + firstName)
    # print("Last Name: " + lastName)
    # print("stdNum: " + stdNum)
    scrubbedStudentFolder = destinationFolder+"\\"+str(hash(firstName))+"-"+str(hash(lastName))+"-"+str(hash(stdNum))
    os.mkdir(scrubbedStudentFolder)
    for filename in listdir(folder+"\\"+studentSubmission):
        if filename.endswith(".java") or filename.endswith(".cpp") or filename.endswith(".c") or filename.endswith(".hpp") or filename.endswith(".h"):
            #scrub data
            f = open(folder+"\\"+studentSubmission+"\\"+filename).read()
            replace = f.replace(firstName, str(hash(firstName))).replace(lastName, str(hash(lastName))).replace(stdNum, str(hash(stdNum)))
            newF = open(scrubbedStudentFolder+"\\Scrubbed-"+filename, 'w')
            newF.write(replace)
            newF.close()