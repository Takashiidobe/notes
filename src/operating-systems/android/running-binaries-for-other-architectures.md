---
title: Running binaries for other architectures
date created: Sunday, February 2nd 2025, 9:30:22 am
date modified: Sunday, February 2nd 2025, 9:37:12 am
---

Say you have a computer that is an x86_64 computer:

```sh
$ uname -m
x86_64
```

But you want to run a binary for another architecture, like arm64:

```sh
$ file collections
collections: ELF 64-bit LSB executable, ARM aarch64, version 1 (SYSV), statically linked, Go 
```

Normally if you run the binary, you'll get an error:

Instead, you can actually run it by emulating the architecture you need. Install qemu-user and qemu-user-static to run binaries:

```sh
sudo dnf install qemu-user qemu-user-static
```

And you should be able to run the file.