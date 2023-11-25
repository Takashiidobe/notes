---
title: "Disk and File Management"
---

# Disk and File Management

Prev: [jdbc](jdbc.md)
Next: [memory-management](memory-management.md)

Access to disk drives can be slow. To improve access speeds, disks might contain volatile caches, which may not be durable memory. Writes are persisted in the cache before the SSD.

A few ways to improve latency are:

Disk Striping: using multiple disk drives, with a controller that handles distributing writes to the n disks it controls.

Reliability can be improved by mirroring writes to disks, so changes are persisted more than once.

To reduce the memory requirement, parity blocks can be recorded instead.

All of these methods can be combined in RAID.

The SimpleDB file manager stores data in pages, and owned by a File Manager.

A block, or a part of a page that has data written to it, is encapsulated in a block.

There are three implementations:

```rust
struct BlockId {
    filename: String;
    blknum: i32;
}
```

```rust
struct Page {
    bb: Vec<u8>,
}
```

```rust
struct FileMgr {
    db_directory: File,
    block_size: i32,
    is_new: bool,
    open_files: HashMap<String, File>,
}
```

Prev: [jdbc](jdbc.md)
Next: [memory-management](memory-management.md)
