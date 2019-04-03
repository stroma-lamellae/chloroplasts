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

#TODO this will be in a config file where the results are stored
if not os.path.exists(os.path.join(config["DISK"]["RESULT"], "Results")):
    os.mkdir(os.path.join(config["DISK"]["RESULT"], "Results"))

if not os.path.exists(os.path.join(config["DISK"]["Queue"], "Queue")):
    os.mkdir(os.path.join(config["DISK"]["Queue"], "Queue"))

thread = Thread(target=sub missionQueue.processQueue)
thread.start()

# If we're running in stand alone mode, run the application
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=3000, debug=True)
    thread.join()
