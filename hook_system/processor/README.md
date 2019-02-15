Readme for the Processing Server
# User Guide

# Development Guide

## Prerequisites for the processing system
1. Python 3 installed on system
2. Python3-pip installed on system
3. python3-virtualenv installed on the system

To first create your virtual enviroment for python run the command `virtualenv -p /usr/bin/python3 env`, for windows instead of `/usr/bin/python3` put the path to your python3 interpreter. 

The next step is to install the dependencies in your virtual enviroment, run the command `source env/bin/activate` to activate the virtual python enviroment. **NOTE**: You will need to run this command everytime you open up a new terminal to run the python code or else it will not be able to find the dependencies.

After launching the virtual enviroment you will need to install the dependencies for the first time, to do this run `pip3 install -r requirements.txt`. **NOTE**: Please if you change any dependencies while developing update the requirements.txt document by running `pip3 freeze`, this will show which dependencies are installed in the virtual enviroment.

## The REST Server

The package being used to run the REST server is called *Connexion*, the list of API calls are defined in the *swagger.yml* file and the comments in the file should be sufficient enough to understand on how to modify or create new ones as needed.

To access the UI page for the API go open up the following link **http://\<ip-address>:\<port>/api/ui** where the ip address and port are specified in the *server.py* file