import configparser
import os.path, os
import errno

dir_path = os.path.dirname(os.path.realpath(__file__))
fullConfig = os.path.join(dir_path, "config.ini")

def createConfig():

    #Database info
    db_name = input("Enter the database name: ")
    db_user = input("Enter the database user: ")
    db_password = input("Enter the database password: ")

    #Email info
    fromEmail = input("Enter address of Email to send from: ")
    fromPass  = input("Enter password for Email: ")
    smtpServer= input("Enter SMTP server for Email: ")
    smtpPort  = input("Enter SMTP port for Email: ")

    resultsPath = input("Enter Full Path For Results Folder to be Created: ")
    queuePath   = input("Enter Full Path For Queue Folder to be Created: ")

    config = configparser.ConfigParser()

    config["DATABASE"] = {'database_name': db_name, 'database_user': db_user,
            'database_password':db_password}
    config["EMAIL"]    = {'FromAddr': fromEmail, 'FromPassword': fromPass,
            'SMTP_Server':smtpServer, 'SMTP_Port': smtpPort}

    config["DISK"] = {'queue': queuePath, 'result': resultsPath}

    with open(fullConfig, 'w') as f:
        config.write(f)

    print("Setup Complete!")

def removeIfExists(filename):
    try:
        os.remove(filename)
    except OSError as e:
        if e.errno != errno.ENOENT:
            raise

if os.path.isfile(fullConfig):
    print("Configuration file already present. You can edit with a text editor if you wish to make individual changes.")
    print("Continuing will completely overwrite previous configurations.")

    userInput = input("Enter [Y] to continue, Enter [q] or just close the program to cancel:")

    if userInput.lower() == 'q':
        print("Cancelling Now, no changes were made to your configurations.")
        exit(0)
    elif userInput.upper() == 'Y':
        createConfig()
    else:
        print("Abort.")
        exit(0)
else:
    createConfig()
