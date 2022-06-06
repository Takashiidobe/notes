---
title: "Reflections on Trusting Trust"
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
