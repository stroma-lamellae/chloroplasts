# Client Server Installation

The following has been tested on Ubuntu 18.04 LTS, the system should work on any modern Unix like OS that is supported by dotnet. Run the following commands to install the dependencies required.

```bash
#Dotnet 2.2
wget -q https://packages.microsoft.com/config/ubuntu/18.04/packages-microsoft-prod.deb
sudo dpkg -i packages-microsoft-prod.deb
sudo add-apt-repository universe
sudo apt-get install apt-transport-https
sudo apt-get update
sudo apt-get install dotnet-sdk-2.2
rm packages-microsoft-prod.deb

#PostgreSQL
sudo apt-get install postgresql

#Nodejs & npm
sudo apt install nodejs npm

#Python dependencies
sudo apt-get install python3-dev python-virtualenv
```

## Set up the client database
- login to the database with `sudo -i -u postgres psql` then set up the database and users. Replace `clientserver`, `clientuser`, and `password` with your desired database name, database user, and password, and then update the `appsettings.json` to reflect what you set them to.

```
CREATE DATABASE clientserver;
CREATE USER clientuser WITH ENCRYPTED PASSWORD 'password';
GRANT ALL PRIVILEGES ON DATABASE clientserver TO clientuser;
```

- Setup the schema with the following
```
dotnet ef migrations add InitialCreate
dotnet ef database update
```

## Set up scrubbing script
- Locate the scrubbing folder inside the client code folder then create a virtual environment and install the the dependencies in it.
```
virtualenv -p python3 env
source env/bin/activate
pip install -r requirements.txt
```

## Set up webserver
- Start by installing NGINX, `sudo apt-get install nginx`.
- Run `dotnet publish -c Release` inside the ClientServer folder, this will create a release inside `./bin/Release/netcoreapp2.2/publish/`. Now copy that `publish/` folder to `/var/www/` and name the folder `ClientServer`.
- Set up the NGINX server as a reverse proxy, create a file named `/etc/nginx/sites-available/default` with the following text (`default` can be changed to anything you want).
```
server {
    listen      80;
    server_name domainname.com www.domainname.com;

    location / {
        proxy_pass          http://localhost:5000;
        proxy_http_version  1.1;
        proxy_set_header    Upgrade $http_upgrade;
        proxy_set_header    Connection keep-alive;
        proxy_set_header    Host $host;
        proxy_cache_bypass  $http_upgrade;
        proxy_set_header    X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header    X-Forwarded-Proto $scheme;
    }
}
```

- This sets up the server for HTTP only. Before NGINX implements the configuration you need to create a link of this file into the enabled folder with the following command `sudo ln -s /etc/nginx/sites-available/default /etc/nginx/sites-enabled/`. Restart NGINX to implement the changes made with `sudo nginx -s reload`.

- Now setup the kestrel server for dotnet, create a file called `/etc/systemd/system/kestrel-ClientServer.service` with the following text. If you didn't put the application in `/var/www/` then replace it with where ever you put it, but make sure to change the folder ownership and permissions.
```
[Unit]
Description=Hook Client

[Service]
WorkingDirectory=/var/www/ClientServer
ExecStart=/usr/bin/dotnet /var/www/ClientServer/ClientServer.dll
Restart=always
# Restart service after 10 seconds if the dotnet service crashes:
RestartSec=10
KillSignal=SIGINT
SyslogIdentifier=hook-clientserver
User=www-data
Environment=ASPNETCORE_ENVIRONMENT=Production
Environment=DOTNET_PRINT_TELEMETRY_MESSAGE=false
TimeoutStopSec=90

[Install]
WantedBy=multi-user.target
```
- Now enable and start the service.
```
sudo systemctl enable kestrel-ClientServer.service
sudo systemctl start kestrel-ClientServer.service
sudo systemctl status kestrel-ClientServer.service
```

- Make sure that the status says loaded and active, press `q` to quit the log.

- To set up the proxy create a file called `/etc/nginx/proxy.conf` with the following text
```
proxy_redirect          off;
proxy_set_header        Host $host;
proxy_set_header        X-Real-IP $remote_addr;
proxy_set_header        X-Forwarded-For $proxy_add_x_forwarded_for;
proxy_set_header        X-Forwarded-Proto $scheme;
client_max_body_size    10m;
client_body_buffer_size 128k;
proxy_connect_timeout   90;
proxy_send_timeout      90;
proxy_read_timeout      90;
proxy_buffers           32 4k;
```

- Set up the `/etc/nginx/nginx.conf` file by deleting the contents and replacing it with the following, replace the ssl certificate and key file with your own if you already have a CA signed cert for the server being used.

```
user www-data;
worker_processes auto;
pid /run/nginx.pid;
include /etc/nginx/modules-enabled/*.conf;

events {
        worker_connections 768;
        # multi_accept on;
}

http {
    include        /etc/nginx/proxy.conf;
    limit_req_zone $binary_remote_addr zone=one:10m rate=5r/s;
    server_tokens  off;

    sendfile on;
    keepalive_timeout   1000; # Adjust to the lowest possible value that makes sense for your use case.
    client_body_timeout 1000; client_header_timeout 1000; send_timeout 1000;

    upstream hellomvc{
        server localhost:5000;
    }

    server {
        listen     *:80;
        add_header Strict-Transport-Security max-age=15768000;
        return     301 https://$host$request_uri;
    }

    server {
        listen                    *:443 ssl;
        server_name               35.227.54.68;
        ssl_certificate           /etc/ssl/certs/ClientServer.crt;
        ssl_certificate_key       /etc/ssl/private/ClientServer.key;
        ssl_protocols             TLSv1.1 TLSv1.2;
        ssl_prefer_server_ciphers on;
        ssl_ciphers               "EECDH+AESGCM:EDH+AESGCM:AES256+EECDH:AES256+EDH";
        ssl_ecdh_curve            secp384r1;
        ssl_session_cache         shared:SSL:10m;
        ssl_session_tickets       off;
        ssl_stapling              on; #ensure your cert is capable
        ssl_stapling_verify       on; #ensure your cert is capable

        add_header Strict-Transport-Security "max-age=63072000; includeSubdomains; preload";
        add_header X-Frame-Options DENY;
        add_header X-Content-Type-Options nosniff;

        #Redirects all traffic
        location / {
            proxy_pass http://hellomvc;
            limit_req  zone=one burst=10 nodelay;
        }
    }
}
```

## Creating a CA signed cert

- If you already have a domain name but don't have a CA signed cert for the server do the following to create and install one.

```
sudo add-apt-repository ppa:certbot/certbot
sudo apt install python-certbot-nginx
```

- Make sure you have the correct `server_name domainname.com www.domainname.com` in the `/etc/nginx/sites-available/default` file before continuing.

```
sudo certbot --nginx -d domainname.com -d www.domainname.com
```

- Follow the steps in the script and then it should automatically set the certs in the `default` file, the certificate expires every 90 days so to automate the renewel of it run `sudo certbot renew --dry-run`.
