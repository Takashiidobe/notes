---
title: the-chubby-lock-service
---

Chubby Lock Service\"

The Chubby lock service is a coarse-grained lock service (locks that are
held for a long time).

Chubby normally is run in a cluster of 5 (1 master, 4 replicas) that use
paxos to elect a master. DNS finds the replicas, which can connect to
the current master.

The file interface exposed by chubby is simpler than UNIX \-- moving
files from one directory to another is not allowed, directory modified
times are not kept, and last-access times are not kept either.

Writing to a file requires an exclusive lock, whereas reading from a
file does not.
