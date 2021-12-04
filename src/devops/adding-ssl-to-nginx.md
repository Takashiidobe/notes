---
title: adding-ssl-to-nginx
---

Ssl To Nginx

# Adding SSL to Nginx

## Install Nginx first with:

`apt-get update`

`apt install nginx`

## Allow your server to take traffic on port 443

`iptables -A INPUT -p tcp -m tcp –dport 443 -j ACCEPT`

in `/etc/nginx/sites-available/default`, change the body to look
something like this:

    ssl on;

    ssl_certificate /etc/ssl/fake.cert;

    ssl_certificate_key /etc/ssl/fake.key;
    listen 443 ssl default_server;
    listen [::]:443 ssl default_server;

    root /var/www/html;

    index index.html index.htm index.nginx-debian.html;

    server_name _;
    location / {
      proxy_pass http://localhost:3000;
      proxy_set_header X-Real-IP $remote_addr;
      proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
      proxy_set_header Host $http_host;
      proxy_set_header X-NginX-Proxy true;
      # Enables WS support
      proxy_http_version 1.1;
      proxy_set_header Upgrade $http_upgrade;
      proxy_set_header Connection "upgrade";
      proxy_redirect off;
    }

This routes requests from port 3000 to 443, using an SSL certificate key
from `/etc/ssl/fake.key` and a certificate from `/etc/ssl/fake.cert`

We can generate these certs on any computer with openSSL installed.

generate a key with `openssl genrsa -out ${domain_name}.key 2048`

create a new file `${domain_name}.conf` with:

    [req]
    distinguished_name=req
    [SAN]
    subjectAltName=DNS:${domain_name}

create the cert with:
`openssl req -new -x509 -key 172.105.152.49.key -out 172.105.152.49.cert -days 3650 -subj /CN=172.105.152.49 -extensions SAN -config '172.105.152.49.conf'`

- Run the app with `nohup path_to_binary &`. This will render a long
  running process that will live after you ssh out.
