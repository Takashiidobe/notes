---
title: Restart Caddy on Startup
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Saturday, November 9th 2024, 7:24:46 am
---

# Restart Caddy on Startup

Here\'s a systemd file that will restart a caddy server when the server
restarts.

Place this file in `/etc/systemd/system/caddy.service` on an ubuntu
server.

```sh
[Unit]
Description=Caddy
Documentation=https://caddyserver.com/docs/
After=network.target

[Service]
User=caddy
Group=caddy
ExecStart=/usr/bin/caddy run --environ --config /etc/caddy/Caddyfile
ExecReload=/usr/bin/caddy reload --config /etc/caddy/Caddyfile
TimeoutStopSec=5s
LimitNOFILE=1048576
LimitNPROC=512
PrivateTmp=true
ProtectSystem=full
AmbientCapabilities=CAP_NET_BIND_SERVICE

[Install]
WantedBy=multi-user.target
```
