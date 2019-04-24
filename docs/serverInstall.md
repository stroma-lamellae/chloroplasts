# Processing Server Installation

The following has been tested on Ubuntu 18.04 LTS but should work as well on any system running a minimum python version of 3.6.7, and Apache 2.4.

## PostgreSQL 

- Start by installing postgreSQL
```
sudo apt-get update
sudo apt-get install postgresql
```

- Change the default postgres password to something secure with `sudo passwd postgres`
- Now create a database and user for the processing server. Replace `dbName` and `userName` with the desired database name and username respectively.
```bash
sudo -i -u postgres
createuser userName -P --interactive #superuser - n, create db - y, create role -y
createdb dbName
sudo adduser userName #leave everything blank except for password if you don't care
```
- Now that postgreSQL is installed log out of the `postgres` user and run `sudo -i -u userName pg_restore --no-owner -d dbName /path/to/dump.dmp` to restore the database. If for any reason you need to back up the schema run the following command `pg_dump -Fc dbName > dump.dmp`

## Source Code

- Copy the the `app.wsgi` file, `requirements.txt` file and `Src/` folder to a desired running directory.

- Run the `setup.py` configuration setup file inside the `Src/` folder and follow the instructions in the script. **NOTE:** The path that is specified for the Queue and Results must already exist or else the processing server will crash. Also the folder you specify must have r/w/x permissions for the `www-data` user, this can be done with `setfacl -m u:www-data:rwx aFolder`.

- Open a terminal inside the `Src/` folder and enter the following commands
```
sudo apt-get install python-virtualenv
virtualenv -p python3 ./env
source env/bin/activate
pip install -r ../requirements.txt
```
- The dependencies should now be satisfied and you can test if they are installed correctly by running `python __init__.py`, if it runs correctly you can continue.

- Now that the code is running it is time to install the webserver to run it on. It is also possible to use NGINX but it has not been tested. To install apache and WSGI run the following commands:
```
sudo apt-get update
sudo apt-get install apache2 libapache2-mod-wsgi-py3
sudo a2enmod wsgi 
```

- If you plan to run the webserver on a port other than 80 or 443 you must modify the `/etc/apache2/ports.conf` file by adding a new *Listen* line specifying which port to listen on.

- Create an empty folder inside the `Src/` folder named `static`.

## If the server has a FQDN then skip this section
## To install TLS with self signed certificate:
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

- Now create a file `/etc/apache2/sites-available/app.conf` with the text below replacing `/home/4F00/chloroplasts/` with the running directory chosen earlier.
```
<IfModule mod_ssl.c>
<VirtualHost *:port>
	ErrorLog /home/4F00/chloroplasts/error.log
	LogLevel info
	CustomLog /home/4F00/chloroplasts/access.log combined

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

- This should enable the webserver with WSGI and TLS. The certificate expires one year from the day you create it, so it will have to be renewed manually every year.

## If the server has a FQDN then you can use a CA signed cert
 
- First run the following commands
```
sudo add-apt-repository ppa:certbot/certbot
sudo apt-get update
sudo apt-get install python-certbot-apache
```

- Then create a file `/etc/apache2/sites-available/app.conf` with the text below replacing `/home/4F00/chloroplasts/` with the running directory chosen earlier and `dn.tld` with your FQDN.
```
<VirtualHost *:port>
	ServerName dn.tld

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

- Now run the command `sudo certbot --apache -d dn.tld -d www.dn.tld` and follow the instructions in the script. Everything should be set up automatically by Let's Encrypt, you can run a `apachectl configtest` to test the configuration of Apache. If the configtest fails but certbot didn't throw any errors verify that the following lines were inserted into your `app.conf` file.
```
Include /etc/letsencrypt/options-ssl-apache.conf
SSLCertificateFile /etc/letsencrypt/live/www.facialstats.com/fullchain.pem
SSLCertificateKeyFile /etc/letsencrypt/live/www.facialstats.com/privkey.pem
```

- If the configtest is successful then run the following commands to enable the site and restart Apache.
```
sudo a2ensite app
sudo systemctl restart apache2
```

- This is optional but recommended as the certificate expires every 90 days.
  - Open up a terminal and enter `sudo crontab -e` then add the following line to the end of your cronjob file `15 3 * * * /usr/bin/certbot renew --quiet`. This renews the cert if it is set to expire in the next month.