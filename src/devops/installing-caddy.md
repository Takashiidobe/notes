---
title: installing-caddy
---
# Installing Caddy

- Install caddy by going to the github page: -
  `https://github.com/caddyserver/caddy/releases` - `wget` the link
  you need (linux_amd64.tar.gz) and unpack the zip file with -
  `tar -xvzf caddy_version_os_arch.tar.gz`. - Move the file over to
  `/usr/local/bin` with `mv caddy /usr/local/bin/caddy`.

## Domain Configuration

- With a Google Domain, Go to the Custom Resource Records, and set an
  `A` level record with a `TTL` to `1h` and set the data field to the
  IPv4 address you have configured.
- Wait for about 5 minutes for the changes to take effect.
- Port 80 and Port 443 must be open.
- Run the following commands to open traffic to port 80 and 443.
- `sudo iptables -A INPUT -p tcp -m multiport --dports 80,443 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT`

## Persisting iptable rules

- `sudo apt-get install iptables-persistent` will allow iptable rules
  to become persistent.
- at any time if you update rules, run
  `sudo netfilter-persistent save` to have them persist.

## Running the Caddyfile

- Create a Caddyfile with the following contents

```{=html}
<!-- -->
```

    domain.com

    respond "Hello, Https!"

- Then, when you go to the domain, you should notice the server being
  served over https with a cert from letsencrypt.

## As Reverse Proxy

- You can also use Caddy as a reverse proxy:
- run your server on a different port and have it route to it by using
  this `caddyfile`

```{=html}
<!-- -->
```

    domain.com

    reverse_proxy 127.0.0.1:${PORT}
