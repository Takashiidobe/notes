---
title: "A Case for Redundant Array of Inexpensive Disks (RAID)"
---

This paper was published by Patterson, Gibson, and Katz in 1988.

The motivation behind RAID was the slow improvement in disk performance
in comparison to CPU improvements.

Because of Amdahl's law, if 90% of the time of a program was seeking for
data, if CPU improved 2x, but data seeking didn't, then the program
would only be 5% faster.

Instead of using expensive high end disks, the authors propose using
cheap, inexpensive disks for storage. Writes may write data to more than
one disk, which slows writes, in exchange for faster reads. However,
reliability also increases, because there are many copies of the same data.

## RAID 0

Raid 0 is a scheme where data is striped across the disks without any
increased redundancy.

## RAID 1

Raid 1 refers to mirroring the same data across two disks. Reads and
writes are both slower under this scheme, but reliability is improved
because the system can tolerate failure of one of the disks.

## RAID 2

RAID 2 involves using error correcting codes (ECC) for redundant data.
This isn't as popular nowadays, since the firmware of most disks
involves handling for corrupt data (fail-stop mode), where if a read is
issued to corrupt data, it provides no data at all instead of corrupt
data. Nonetheless, it is a way to provide in software what might not be
guaranteed by hardware.

## RAID 3

RAID 3 is similar to RAID 2, except it uses a parity XOR bit to store
data. In the case of a disk-failure, the controller can reconstruct lost
data from parity data.

This is extremely inefficient for small writes, since they have to read
a sector from disk, modify it, and then write back the entire sector.

## RAID 4

RAID 4 is the same as RAID 3, just that it uses striping in contiguous
sectors, which makes serial reads and writes a bit better.

## RAID 5

RAID 5 spreads out the parity sector across the disks in a round robin
manner -- so each disk has some data and some parity bits. This helps
improve serial reads and writes, and improves redundancy, since losing
one disk is fine most of the time.
