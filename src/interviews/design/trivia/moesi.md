# MOESI protocol

MOESI is an addition to the previous protocols, MESI and MSI.

MOESI stands for:

- Modified: The cache owns the only valid copy of the cache line, and made changes to it.
- Owned: The cache owns a valid copy of the cache line, but with the exclusive write to make changes to it. If changes are made to it, then the changes must be broadcast to everybody else.
- Exclusive: The cache has the only copy of the line, but the line is clean.
- Shared: The cache has one of many copies in the line, but cannot modify it.
- Invalid: The block is invalid, it must be fetched from main memory.
