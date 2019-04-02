#!/usr/bin/python3
import logging
import sys
logging.basicConfig(stream=sys.stderr)
sys.path.insert(0, '/home/4F00/flask/') #TODO config file reading
from Src import app as application