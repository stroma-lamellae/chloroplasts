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

#save hash in the database
try:
    conn = psycopg2.connect(host="localhost", database="clientserver", user="clientserver", password="password")
    cursor = conn.cursor()
except:
    print("error connecting to the database")

for section in listdir(folder):
    os.mkdir(destinationFolder+"\\"+section)
    if section == "Current Year" or section == "Previous Years":
        for studentSubmission in listdir(folder+"\\"+section):
            try:
                firstName, lastName, stdNum = studentSubmission.split("-")
                #save hash in the database HERE
                #cur.execute("INSERT INTO table_name_here (column_names_here) VALUES (values_here)")
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
                #this code will be executed if the folder is not named properly
                unScrubbedFolders = "\t" + studentSubmission + "\n"

#if any folder causes an exception, then show an alert at the end with the summary
if unScrubbedFolders != "":
    alertMessage = "Some submissions were not able to be scrubbed. They are listed below:\n"
    alertMessage = alertMessage + unScrubbedFolders
    ctypes.windll.user32.MessageBoxW(0, alertMessage, "Alert", 1)

if conn is not None:
    conn.close()