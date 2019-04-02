import configparser
import os.path, os
import errno
import sqlite3

configFilename = "/config.ini"
dir_path = os.path.dirname(os.path.realpath(__file__))

fullConfig = dir_path + configFilename

def createConfig():

    #Database info
    db_name = input("Enter the URL for Impact Auto's search query: ")
    db_user = input("Enter the car model searching for: ")
    db_password = input("Enter the older possible year for the car or leave blank for no limit: ")

    #Email info
    fromEmail = input("Enter address of Email to send from: ")
    fromPass  = input("Enter password for Email: ")
    smtpServer= input("Enter SMTP server for Email: ")
    smtpPort  = input("Enter SMTP port for Email: ")

    config = configparser.ConfigParser()

    config["DATABASE"] = {'database_name': db_name, 'database_user': db_user,
            'database_password':db_password}
    config["EMAIL"]    = {'FromAddr': fromEmail, 'FromPassword': fromPass,
            'SMTP_Server':smtpServer, 'SMTP_Port': smtpPort}

    with open(fullConfig, 'w') as f:
        config.write(f)

    print("Setup Complete!")


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
