---
title: setup-git-on-server
---

Git On Server

# Setup Git on a Server

First, ssh or otherwise login to your remote server:

Next, install git on the server.

```sh
sudo apt update && sudo apt install git
```

Next, create a new user that will manage the Git Repos:

```sh
sudo useradd -r -m -U -d /home/git -s /bin/bash git
```

Switch over to the git user with `sudo su`

```sh
sudo su - git
```

Make the folder you want to in the home directory:

```sh
mkdir project_name.git
```

Next, make the `~/.ssh` directory for the user and set the correct
permissions:

```sh
mkdir -p ~/.ssh && chmod 0700 ~/.ssh
```

Next, create the authorized keys file and set it to have permissions of
`0600`.

```sh
touch ~/.ssh/authorized_keys && chmod 0600 ~/.ssh/authorized_keys
```

Next, move your ssh keys to the server\'s authorized keys:

On your local machine:

```sh
cat ~/.ssh/id_rsa.pub
```

And copy paste it into the authorized keys file:

```sh
sudo vim /home/git/.ssh/authorized_keys
```

now add your git remote to the local repository you took the rsa key
from:

```sh
git remote add server git@{server_ip}:project_name.git
```

and push!

```sh
git push -u server master
```
