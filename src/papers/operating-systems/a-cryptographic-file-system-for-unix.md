---
title: "A Cryptographic File System For Unix"
pdf_url: "[[a-cryptographic-file-system-for-unix.pdf]]"
---
This paper discusses a system that provides an encrypted file system by integrating encryption into the Unix file system interface. They call it CFS.

Some goals for CFS:

- Keys should be supplied only **once** per session
- Encrypted files should behave just like normal unix files
- Performance should be acceptable
- Protection of contents + metadata
- No cleartext should go to the server
- Only require client side trust; the server doesn't need to be trusted.

A few of the unix cli calls are changed to work with encryption:
- `cmkdir`
- `cattach <encrypted-dir> <name>`
- `cdetach <name>`
- `cname`
- `ccat`

CFS only has client-side encryption, uses DES, and uses a userspace daemon, called `cfsd` to handle caching and access of files.

I think the paper aged well, but in 2025 there are a lot of complaints:

- No authentication: Only confidentiality, which means that you can't really tell if bits were tampered. 
- Dictionary attacks are easy to levy on this system, because there's no salt.
- The metadata that's shown, file sizes, timestamps, dir structure, and access patterns, allow an attacker to figure out what you're working on even without breaking encryption. 
- The local machine is fully trusted: Any compromise on your machine where a process could get root, and then read the daemon's plaintext memory is pretty easy. There's also no note of clearing memory, so reading caches or swap or process memory would also go around encryption.
- There's one key used, which can stay in memory or caches. As well, there wasn't any hardware support for HSMs, so any crash or memory put in swap will leak the key.
