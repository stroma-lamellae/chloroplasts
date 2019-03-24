import psycopg2
import argparse
import hashlib
import sys

parser = argparse.ArgumentParser()
parser.add_argument('-user', type=str,required=True, help='database user')
parser.add_argument('-password', type=str,required=True, help='database password')
exclusive = parser.add_mutually_exclusive_group(required=True)
exclusive.add_argument('-add', type=str, help='add an authorized insitution')
exclusive.add_argument('-remove', type=str, help='remove an authorized institution')
exclusive.add_argument('-change', type=str, help='change an existing authroized institution')

args = parser.parse_args()

dbUsername = args.user
dbPassword = args.password

try:
    conn = psycopg2.connect(host="localhost", database="hookserver", user=dbUsername, password=dbPassword)
    cur = conn.cursor()
except:
    #will stop execution and send back the error message
    sys.exit("error connecting to the database")

if args.add:
    add()
elif args.remove:
    remove()
elif args.change:
    change()



def add():
    try:
        cur.execute("SELECT School_Name FROM Institutions WHERE License_Number = %s", (args.add))
        inst = cur.fetchone()
        print(inst)
        if inst is None:
            inst = input("Licence not found in Database. Enter New Institution name:\n")
        username = input("Enter the name of the person identified with this license:\n")
        email = input("Enter their email address:\n")
        userid = hashlib.sha1()
        userid.update(email)
        userid.hexdigest
        cur.execute("INSERT INTO \"Institutions\"(\"License_Number\",\"School_Name\", " +
                "\"User_ID\",\"User_Name\", \"User_Email\") VALUES " +
                "(%s, %s, %s, %s, %s);", (args.add, inst,userid, username,email))

    except:
        sys.exit("Unable to insert into database")

def remove():
    try:
        cur.execute("SELECT School_Name FROM Institutions WHERE License_Number= %s", (args.remove))
        inst = cur.fetchone()
        print("The following records are associated with that licence: "+inst)
        useremail = input("Enter the email address of the user you would like " +
        "to remove or type 'all' to remove all records associated with this" +
        "license")
        cur.execute("DELETE FROM Institutions WHERE License_Number= %s AND +"
        "User_Email= %s", (args.remove, useremail))

    except:
        sys.exit("Unable to insert into database")


def change():
    print("Implement me!")




conn.commit()

#close the database connection
if conn is not None:
    conn.close()

#completed successfully
sys.exit(None)

