# How does a Shell work?

The shell works by first parsing the commands provided by the user into some AST. Then, it goes to each node and runs code differently for each type.

If it finds a node and realizes it is an alias, it will try to reduce it to either a builtin or a binary.

If a binary is found, it'll fork a new process, execve the binary, and then capture its stdout, stdin, and stderr.

If it is a builtin, it can execute code on its own process.
