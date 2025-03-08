# Disk I/O

This lecture focuses on disk I/O and buffers.

A Disk Device (Virtio-Disk) transfers blocks of size 1024B.
A sector is the smallest addressable unit by physical media. This is
generally smaller than a block.

The second block in xv6 contains metadata about how many blocks are
allocated and other stuff.

Reads and writes can be done by `virtio_disk_rw(buf_ptr, 0)` or
`virtio_disk_rw(buf_ptr, 1)` which either does a read or write.
