---
title: "Dsync Efficient Block Wise Synchronization Of Multi Gigabyte Binary Data"
pdf_url: "[[dsync-efficient-block-wise-synchronization-of-multi-gigabyte-binary-data.pdf]]"
---
This paper introduces `dsync`, which is a block-level synchronization mechanism for large binary files. It does this by tracking changes online in the Linux Kernel instead of discovering them later. This allows for periodic synchronization by only sending the blocks that changed, and much faster + less cpu than userspace tools like rsync.

For a very large disk (hundreds of TBs) reading all bytes once already can take longer than an hour. Running a checksum over those blocks also incurs CPU over that as well.

Note that most of the time, only a few blocks change -- so just send those blocks.

## Implementation

1. `dsync` hooks into the linux device mapper as a new target that wraps a block device.
2. For every write, it marks a given block as dirty in-kernel.
3. At sync time, a user-space tool reads the dirty bitmaps and only sends those blocks.

- Because you only need one bool per block, with a 4KB block, a 4TB disk only needs 128MB of RAM, which is not much RAM overhead.

In the Kernel: just need to extend `map()` to set the corresponding bit on a block write.

In Userspace: expose per-device tracking:

- read: to list modified block numbers
- write: to clear the bitmap after a successful sync

## Results

dsync is competitive with ZFS, taking about 7 minutes on the author's computer to sync a synthetic file, and 5x as fast as rsync, which becomes CPU bound. It's even faster on SSD.

My thoughts is that I would rather use ZFS, since both use a lot of RAM (ZFS would use about 1GB of RAM for 1TB of storage, and dsync would be 32MB for the same storage).

dsync also works on all file systems, not just ZFS ones, and all devices, with similar performance for the syncing use case, which is somewhat compelling.