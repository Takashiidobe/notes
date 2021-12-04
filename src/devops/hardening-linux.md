---
title: hardening-linux
---

Linux

# Hardening Linux

First, create a new Debian based VM (Debian or Ubuntu).

next, run this command to run the script that will harden the server:
wget -q https://sot.li/hardensh -O init-linux-harden.sh && bash
./init-linux-harden.sh -d -q -hide

Run the tail command to get the username, password, passphrase, and key
pair for the new user to login as. Add the key to your \~/.ssh folder
and delete the line in your \~/.ssh/known_hosts file that contains the
ip address to the VM. Next you\'ll want to run:

```sh
ssh-agent
```

copy paste the top two lines it emits then:

```sh
ssh-add ${path_to_key}
```

Enter the passphrase for the key.

Finally, set an alias in your .bashrc file for the ssh command to invoke
the ssh login, since this can be a pain to type out. And you\'re done: a
fully secured VM in a few minutes that is ready to serve traffic.
