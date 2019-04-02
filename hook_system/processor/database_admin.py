import psycopg2
import bcrypt
import argparse
import hashlib
import sys
import configparser
import os



def add_user():
    try:
        licence_hash = bcrypt.hashpw(bytes(args.add, "utf-8"), bcrypt.gensalt())
        licence_string = licence_hash.decode("utf-8")
        select_licensed_institution = "SELECT licence_number FROM institutions WHERE institution_name = %s;"
        cur.execute(select_licensed_institution, (args.institution-name, ))
        inst = cur.fetchone()
        if inst is None:
            new_inst = input("Licence not found in Database. Create new "+
                    "institution? Y/N:\n")
            if new_inst == 'Y':
                inst = add_institution(licence_string)
                print("here")
            else:
                sys.exit("Cannot create user with invalid licence")
            #todo: list institutions + ids
        if not bcrypt.hashpw(bytes(args.add, "utf-8"), bytes(inst[0], "utf-8")) == inst[0]:
            sys.exit("Institution already registered with a different licence. Please use the exisiting licence")
        username = input("Enter the name of the person being added to this licence:\n")
        email = input("Enter their email address:\n")
        userid = hashlib.sha1()
        userid.update(bytes(email, "utf-8"))
        userid.hexdigest()
        insert_new_account = "INSERT INTO accounts(licence_number,user_id,user_name,user_email) VALUES (%s, %s, %s, %s);"
        cur.execute(insert_new_account, (licence_string,userid,username,email))

    except:
        sys.exit("Unable to insert into database")

def remove():
    try:
        cur.execute("SELECT * FROM institutions WHERE licence_number= %s;", (args.remove))
        inst = cur.fetchone()
        cur.execute("SELECT * FROM accounts WHERE licence_number= %s;", (args.remove))
        accts = cur.fetchone()
        jobs = ""
        if accts:
            cur.execute("SELECT * FROM jobs WHERE user_email= %s;",(accts[1]))
            jobs = cur.fetchone()
        print("The following records are associated with that licence:"+
        inst+"\n"+accts+"\n"+jobs)
        useremail = input("Enter the email address of the user you would like " +
        "to remove or type 'all' to remove all records associated with this" +
        "licence")
        if useremail == "ALL":
            cur.execute("DELETE FROM institutions WHERE licence_number = %s;",
            (args.remove))
        else:
            cur.execute("DELETE FROM accounts WHERE licence_number = %s AND +"
        "user_email= %s", (args.remove, useremail))

    except:
        sys.exit("Unable to insert into database")


def change():
    print("Implement me!")




def add_institution(licence):
    inst_name = input("Enter the name of the institution:\n")
    inst_address = input("Enter the address of the institution:\n")
    sys_admin = input("Enter the sysadmin or contact person at this institution:\n")
    sys_admin_email = input("Enter the primary email associated with the institution:\n")
    insert_new_institution = "INSERT INTO institutions(licence_number,institution_name, institution_address, contact_name,contact_email) VALUES (%s, %s, %s, %s, %s);"
    cur.execute(insert_new_institution, (licence,inst_name,inst_address,sys_admin,sys_admin_email))
    conn.commit()


dir_path = os.path.dirname(os.path.realpath(__file__))
configFilename = os.path.join(dir_path,"config.ini")

if not os.path.isfile(configFilename):
    print("No configuration file found. Please run Setup before running this.")
    exit(0)

config = configparser.RawConfigParser()
config.read(configFilename)

parser = argparse.ArgumentParser()
parser.add_argument('-institution-name', type=str,required=True, help='name of institution affiliated wtih the licence')
exclusive = parser.add_mutually_exclusive_group(required=True)
exclusive.add_argument('-add', type=str, help='add an authorized insitution')
exclusive.add_argument('-remove', type=str, help='remove an authorized institution')
exclusive.add_argument('-change', type=str, help='change an existing authroized institution')

args = parser.parse_args()


try:
    conn = psycopg2.connect(host="localhost", database=config["DATABASE"]["DATABASE_NAME"],user=config["DATABASE"]["DATABASE_USER"],password=["DATABASE"]["DATABASE_PASSWORD"])
    cur = conn.cursor()
except:
    #will stop execution and send back the error message
    sys.exit("error connecting to the database")

if args.add:
    add_user()
elif args.remove:
    remove()
elif args.change:
    change()

conn.commit()

#close the database connection
if conn is not None:
    conn.close()

#completed successfully
print("Successfully Entered into Database")
sys.exit(None)
