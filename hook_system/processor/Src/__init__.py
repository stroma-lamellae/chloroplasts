# Copyright (C) 2019 Hook System Authors
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is furnished to do
# so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import connexion
import submissionQueue
from threading import Thread
import os
import configparser

dir_path = os.path.dirname(os.path.realpath(__file__))
configFilename = os.path.join(dir_path,"config.ini")

config = configparser.RawConfigParser()
config.read(configFilename)

# Create the application instance
app = connexion.App(__name__, specification_dir='./')

# Read the swagger.yml file to configure the routes
app.add_api('swagger.yml')

if not os.path.exists(os.path.join(config["DISK"]["RESULT"], "Results")):
    os.mkdir(os.path.join(config["DISK"]["RESULT"], "Results"))

if not os.path.exists(os.path.join(config["DISK"]["Queue"], "Queue")):
    os.mkdir(os.path.join(config["DISK"]["Queue"], "Queue"))

MAX_THREADS = 4

threadList = []

for i in range(MAX_THREADS):
    threadList.append(Thread(target=submissionQueue.processQueue))

for i in range(len(threadList)):
    threadList[i].start()

# If we're running in stand alone mode, run the application
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=3000, debug=True)
    
    for i in range(len(threadList)):
        threadList[i].join()
