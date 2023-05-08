# Read vs. Recv & Send vs Write

`recv()` and `send()` only work on socket descriptors, and let you specify options for the actual operation.

`read()` and `write()` work on any file descriptors.
