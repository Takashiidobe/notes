---
title: Linux File Partitions
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Saturday, November 9th 2024, 7:19:47 am
---

# Linux File Partitions

## Create a File Partition in Linux

To create a file partition in Linux, first list out the information

```sh
$ sudo fdisk -l
Disk /dev/nvme0n1: 1.82 TiB, 2000398934016 bytes, 3907029168 sectors
Disk model: WD_BLACK  SN750 2TB
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: gpt
Disk identifier: 2A58C9A0-B51C-4ADC-BFAC-5B7087910C77

Device           Start        End    Sectors  Size Type
/dev/nvme0n1p1    2048    1230847    1228800  600M EFI System
/dev/nvme0n1p2 1230848    3327999    2097152    1G Linux filesystem
/dev/nvme0n1p3 3328000 3907028991 3903700992  1.8T Linux filesystem


Disk /dev/zram0: 8 GiB, 8589934592 bytes, 2097152 sectors
Units: sectors of 1 * 4096 = 4096 bytes
Sector size (logical/physical): 4096 bytes / 4096 bytes
I/O size (minimum/optimal): 4096 bytes / 4096 bytes
```

Then you'll want to manipulate that disk. Make sure to save, cause all changes are in memory until persisted with `w`. `d` deletes a partition, `n` creates a partition, and `L` lists the partition types, and `t` lets you set the partition number.

```sh
sudo fdisk [disk path]
```

You can then format an external drive with `mkfs`.

Run `sudo mkfs.hfs /dev/sda1` for example to format the first drive as hfs.
