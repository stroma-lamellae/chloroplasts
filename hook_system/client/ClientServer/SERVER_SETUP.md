# Setup instructions for Ubuntu 18.10

## Getting Published Project
- On a computer with the project, navigate the the ClientServer directory and run:
    - `dotnet publish -c Release`
- Zip (or tar or whatever) `ClientServer\bin\Release\netcoreapp2.2\publish`
- Get a database setup file
    - `dotnet ef migrations script > create_database.sql`
- Transfer the zipped file to your server (Going to assume it ends up in `~`, and named `publish.zip`)
- Transfer the database setup script to your server


## Setting up Server
### Getting Dependencies
- `wget -q https://packages.microsoft.com/config/ubuntu/18.10/packages-microsoft-prod.deb`
- `sudo dpkg -i packages-microsoft-prod.deb`
- `sudo apt-get install apt-transport-https`
- `sudo apt-get update`
- `sudo apt-get install dotnet-sdk-2.2`
- `sudo apt-get install unzip`
- `sudo apt-get install nginx`
- `sudo apt-get install postgresql postgresql-contrib`

### Setting up database
- `sudo -i -u postgres`
- `cd /home/usr`
- `psql`
- `CREATE DATABASE clientserver;`
- `CREATE USER clientserver WITH ENCRYPTED PASSWORD 'password';`
- `GRANT ALL PRIVILEGES ON DATBASE clientserver TO clientserver;`
- `\q`
- `psql -d clientserver -f create_database.sql`
- `logout`

### Setting up project
- `unzip publish.zip`
- `sudo cp publish /var/www/ClientServer -r`
- Create a self signed cert (or get a real cert and place in correct location)
    - `sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/ClientServer.key -out /etc/ssl/certs/ClientServer/crt`
- Copy the configuration in `ClientServer/ServerSetupResources/default` from our project into `/etc/nginx/sites-available/default` on the server. This configures nginx to recognize that our app exists, and it will redirect requests there.
- Ensure the configuration is correct, and apply it.
    - `sudo nginx -t`
    - `sudo nginx -s reload`
- Copy the configuration in `ClientServer/ServerSetupResources/service` from our project into `/etc/systemd/system/kestrel-ClientServer.service`. This allows our app to be restarted if there is an issue, or to automatically start the app when the server is restarted.
- `sudo systemctl enable kestrel-ClientServer.service`
- `sudo systemctl start kestrel-ClientServer.service`
- `sudo systemctl status kestrel-ClientServer.service`
- Copy the configuration in `ClientServer/ServerSetupResources/proxy.conf` from our project into `/etc/nginx/proxy.conf`. This sets up the https proxy.
- Copy the configuration in `ClientServer/ServerSetupResources/nginx.conf` from our project into `/etc/nginx/nginx.conf`. This sets up proper https handling.
- `sudo nginx -t`
- `sudo nginx -s reload`

### Monitoring and Updating
- To monitor the app console
    - `sudo journalctl -fu kestrel-ClientServer.service`
- If any changes are made to the ClientServer, you need to stop and restart the service.
    - `sudo systemctl stop kestrel-ClientServer.service`
    - `sudo systemctl start kestrel-ClientServer.service`
    - `sudo systemctl status kestrel-ClientServer.service`