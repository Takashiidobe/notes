---
title: Reflections on Trusting Trust
author:
  - "Ken Thompson"
doi: "10.1145/358198.358210"
url: "https://doi.org/10.1145/358198.358210"
pdf_url: "[[Reflections on trusting trust.pdf]]"
is_oa: true
date created: Saturday, July 19th 2025, 11:02:27 pm
date modified: Sunday, July 27th 2025, 8:56:48 am
---

# Reflections on Trusting Trust

This was Ken Thompson's ACM acceptance speech in 1984.

Unix is written in C. The C Compiler is written in C. Firmware, anything, is generally compiled through a C compiler.

You can't trust code that you didn't write yourself, because if your compiler has been compromised, your compiler can introduce trojan horse like code into binaries.

Let's say that you use a malicious actor's C Compiler that recognizes when it is:

1. Compiling itself.
2. Compiling OS code.

In the case that it's compiling itself, that is bootstrapping another version of the C compiler, it will infect that compiler with the same trojan it has itself.

In the case that it is compiling OS code, it'll inject a trojan that introduces a backdoor into the `login` command that lets the malicious actor login as root.

As long as you don't audit your compiler, your code is compromised.
As well, if you don't audit your OS, your code is compromised.

This requires that you audit everything that your code touches.

Because the compiler itself is bootstrapped from some version long ago, unless you've inspected every version of the compiler that was used to generate your current compiler, you can't verify that there's no backdoor. This is an exercise in obfuscation -- just like in the XZ incident, where there was a m4 script that tried to insert a backdoor into the `sshd` binary listening for connections if it was running on a debian like OS.

Nowadays, we have fully verified compilers -- you can see the source code used to bootstrap your current compiler (rust used an initial compiler to generate a small subset of rust, then uses the previous version of the rust compiler to compile the next version e.g. 1.1 compiles 1.2, and 1.2 is released). However, you can't do this for all software, and with the xz incident, it seems like people are trying to attack all kinds of software with obfuscated tools like m4. In my opinion, writing build scripts with such an obscure turing complete language shouldn't be allowed, but alas, here we are.

[^1]: https://www.cesarsotovalero.net/blog/revisiting-ken-thompson-reflection-on-trusting-trust.html
