# Installation of the Hook System

## System Administration Installation

## Client Server Installation

## Processing Server Installation

The following has been tested on Ubuntu 18.04 LTS but should work as well on any system running a minimum python version of 3.6.7, and Apache 2.4.

### PostgreSQL 

### Source Code

- Copy the the `app.wsgi` file, `requirements.txt` file and `Src/` folder to a desired running directory

- Run the `setup.py` configuration setup file inside the `Src/` folder and follow the instructions in the script. **NOTE:** The path that is specified for the Queue and Results must already exist or else it the processing server will crash.

- Open a terminal inside the `Src/` folder and enter the following commands
  - `python3 -m venv ./env`
  - `source env/bin/activate`
  - `pip install -r requirements.txt`
- The dependencies should now be satisfied and you can test if they are installed correctly by running `python __init__.py`, if it runs correctly you can continue.

- Now that the code is running it is time to install the webserver to run it on. It is also possible to use NGINX but it has not been tested. To install apache and WSGI run the following commands:
```
sudo apt-get update
sudo apt-get install apache2 libapache2-mod-wsgi-py3
sudo a2enmod wsgi 
```

- If you plan to run the webserver on a port other than 80 or 443 you must modify the `/etc/apache2/ports.conf` file by adding a new *Listen* line specifying which port to listen on.

- Create an empty folder inside the `Src/` folder named `static`.

#### If the server has a FQDN then skip this section
#### To install TLS with self signed certificate:
- Run this command to generate the self signed certs
```
sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/apache-selfsigned.key -out /etc/ssl/certs/apache-selfsigned.crt
```

- Now use your favorite text editor to create a file `/etc/apache2/conf-available/ssl-params.conf` with the following text
```
SSLCipherSuite EECDH+AESGCM:EDH+AESGCM:AES256+EECDH:AES256+EDH
SSLProtocol All -SSLv2 -SSLv3 -TLSv1 -TLSv1.1
SSLHonorCipherOrder On
Header always set X-Frame-Options DENY
Header always set X-Content-Type-Options nosniff

SSLOptions +StrictRequire
```

- Now create a file `/etc/apache2/sites-available/app.conf` with the text
```
<IfModule mod_ssl.c>
<VirtualHost *:port>
	# The ServerName directive sets the request scheme, hostname and port that
	# the server uses to identify itself. This is used when creating
	# redirection URLs. In the context of virtual hosts, the ServerName
	# specifies what hostname must appear in the request's Host: header to
	# match this virtual host. For the default virtual host (this file) this
	# value is not decisive as it is used as a last resort host regardless.
	# However, you must set it for any further virtual host explicitly.

	# Available loglevels: trace8, ..., trace1, debug, info, notice, warn,
	# error, crit, alert, emerg.
	# It is also possible to configure the loglevel for particular
	# modules, e.g.

	ErrorLog /home/4F00/chloroplasts/error.log
	LogLevel info
	CustomLog /home/4F00/chloroplasts/access.log combined

	# For most configuration files from conf-available/, which are
	# enabled or disabled at a global level, it is possible to
	# include a line for only one particular virtual host. For example the
	# following line enables the CGI configuration for this host only
	# after it has been globally disabled with "a2disconf".
	#Include conf-available/serve-cgi-bin.conf

	SSLCertificateFile /etc/ssl/certs/apache-selfsigned.crt
	SSLCertificateKeyFile /etc/ssl/private/apache-selfsigned.key
	ServerName ipAddress

	Alias /static /home/4F00/chloroplasts/Src/static
	<Directory /home/4F00/chloroplasts/Src/static>
		<RequireAll>		
			Require all granted
		</RequireAll>
	</Directory>

	<Directory /home/4F00/chloroplasts>
		<Files app.wsgi>
			<RequireAll>
				Require all granted
			</RequireAll>
		</Files>
	</Directory>

	WSGIDaemonProcess myproject python-path=/home/4F00/chloroplasts python-home=/home/4F00/chloroplasts/Src/env
	WSGIProcessGroup myproject
	WSGIScriptAlias / /home/4F00/chloroplasts/app.wsgi

</VirtualHost>
</IfModule>
```

- Then run the following commands
```
sudo a2ensite app
sudo a2enmod ssl
sudo a2enmod headers
sudo a2enconf ssl-params
sudo systemctl restart apache2
```

- This should enable the webserver with WSGI and TLS. The certificate expires one year from the day you create it, so it will have to be renewed every year.

#### If the server has a FQDN then you can use a CA signed cert
 
- First run the following commands
```
sudo add-apt-repository ppa:certbot/certbot
sudo apt-get update
sudo apt-get install python-certbot-apache
```

- Then create a file `/etc/apache2/sites-available/app.conf` with the text
```
<VirtualHost *:port>
		ErrorLog /home/4F00/chloroplasts/error.log
		LogLevel info
		CustomLog /home/4F00/chloroplasts/access.log combined

		Alias /static /home/4F00/chloroplasts/Src/static
		<Directory /home/4F00/chloroplasts/Src/static>
			<RequireAll>		
				Require all granted
			</RequireAll>
		</Directory>

		<Directory /home/4F00/chloroplasts>
			<Files app.wsgi>
				<RequireAll>
					Require all granted
				</RequireAll>
			</Files>
		</Directory>

		WSGIDaemonProcess myproject python-path=/home/4F00/chloroplasts python-home=/home/4F00/chloroplasts/Src/env
		WSGIProcessGroup myproject
		WSGIScriptAlias / /home/4F00/chloroplasts/app.wsgi
</VirtualHost>
```