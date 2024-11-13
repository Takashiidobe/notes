---
title: Time it in Bash
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 8:31:06 pm
---

# Time it in Bash

You can use time to check how long anything takes:

```sh
time ${command}
```

For example, `time host wikipedia.org` returns the following:

```sh
wikipedia.org has address 208.80.154.224
wikipedia.org has IPv6 address 2620:0:861:ed1a::1
wikipedia.org mail is handled by 10 mx1001.wikimedia.org.
wikipedia.org mail is handled by 50 mx2001.wikimedia.org.
host wikipedia.org  0.00s user 0.02s system 27% cpu 0.092 total
```

Portable scripts should use `time -p` since this is consistent with
various implementations:

`time -p sha256sum /bin/ls` should return:

    12477deb0e25209768cbd79328f943a7ea8533ece70256cdea96fae0ae34d1cc  /bin/ls
    real 0.00
    user 0.00
    sys 0.00
