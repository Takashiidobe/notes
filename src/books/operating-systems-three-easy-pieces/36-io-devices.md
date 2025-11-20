---
title: io-devices
---
# I/O Devices

Prev: [[35-a-dialogue-on-persistence]]
Next: [[37-hard-disk-drives]]





## System Architecture

A classical computer system might look like this:

```
CPU         MEMORY
 |             |
<--------------->(Memory Bus)
        |
<----------------> (General I/O Bus (PCI))
        |     |
        |  Graphics
        |
        |
<--------------------> (Peripheral I/O Bus (SCSI, SATA, USB)
 |      |        |
 KB    Mouse    HDD
```

The CPU connects to an I/O chip via DMI (Direct Media Interface from
Intel), Hard Disks might connect via SATA, and Graphics cards via PCI).

The components which are most important are closest to the motherboard,
like the CPU and the memory. Next comes graphics cards, and finally USB
(Hard disks, Mouse and Keyboard).

## A Canonical Protocol

A simplified device interface might look like this:

```
|-------------------------------------|
| Registers | Status | Command | Data |
|-------------------------------------|
| Micro-controller (CPU)              |
| Memory (DRAM or SRAM or both)       |
| Other Hardware-specific Chips       |
--------------------------------------
```

The device has three registers: `status` which holds the status of the
device, `command`, which tells the devices to perform a task, and `data`
to pass data to the device.

An interaction with the device might look like the following:

```c
while (STATUS == BUSY)
  ; // wait until device is not busy
write(fd_data, "something"); // write data
write(fd_command, WRITE_TO_DISK); // command
while (STATUS == BUSY)
  ; // wait until the device completes request
```

This sketch works, but polling is inefficient. It would be better if it
could switch to another CPU while waiting for its command to finish.

## Lowering CPU Overhead with Interrupts

The interrupt can solve this. The OS can issue a request to the device,
put the process to sleep, and then context switch. When the device
finishes, it raises a hardware interrupt, causing the CPU to jump into
the OS at an interrupt handler.

Note that interrupts aren't always better than polling -- if a device
can complete its work with less overhead than a context switch, it
should use polling.

If the device is sometimes fast and sometimes slow, a hybrid approach
might work better.

Other times when polling is better would be for networks, where
interrupt handling can be when there are many requests, and livelock
occurs.

Another optimization is coalescing, where a bunch of interrupts might be
batched into one, to lower the overhead of context switching.

## More Efficient Data Movement with DMA

When using programmed I/O to transfer large amounts of data to a device,
the CPU would be overburdened with copying memory to a disk, which can
take a while. During that time, no processes can run.

Take an example process 1, which copies data during `c`. It then hands
the I/O request over to the disk, which takes care of it, so it can run
another job until it fires an interrupt handler.

```
CPU: 1 1 1 1 1 c c c 2 2 2 2 2 1 1
Disk:                1 1 1 1 1
```

We use Direct Memory Access (DMA) to solve this problem. The OS would
only tell the DMA engine where the data is, how much data to copy, and
which device to send it to. The DMA takes care of the copying, so the
scheduler looks like this:

```
CPU: 1 1 1 1 1 2 2 2 2 2 2 2 2 1 1
DMA:           c c c
Disk:                1 1 1 1 1
```

## Methods of Device Interaction

There are two ways of communicating with I/O devices: either having
specific I/O instructions, or using memory mapped I/O.

### I/O instructions

I/O instructions specify a way for the OS to send data to specific
device registers, like `in` and `out`, which takes a register with data
and a port which names the device. Then, it copies the data to the
device.

### Memory mapped I/O

There is also `memory-mapped I/O`, which uses the `mmap` system call.
The hardware makes device registers available as if they were memory
locations, which can be loaded or stored to.

## Fitting Into the OS: The Device Driver

A final problem is how to make a file system oblivious to the types of
devices it writes to.

We want to support IDE disks, USB, NVMe, SCSI etc. This is done with
abstraction, where the OS supports an interface with error handling, and
reads/writes, and a device driver implements that interface, while
talking to the specific device.

Unfortunately, this encapsulation has its cons. Error handling has to go
to the lowest common denominator, like ATA/IDE drives, even though SCSI
devices have much better error handling. Thus, Linux's error reporting
is a generic EIO (generic IO error code).

## Case Study: A Simple IDE Disk Driver

```
Control Register:
  Address 0x3F6 = 0x08 (0000 1RE0): R=reset,
    E=0 means "enable interrupt"
Command Block Registers:
  Address 0x1F0 = Data Port
  Address 0x1F1 = Error
  Address 0x1F2 = Sector Count
  Address 0x1F3 = LBA low byte
  Address 0x1F4 = LBA mid byte
  Address 0x1F5 = LBA hi byte
  Address 0x1F6 = 1B1D TOP4LBA: B=LBA, D=drive
  Address 0x1F7 = Command/status
Status Register (Address 0x1F7):
  7 6 5 4 3 2 1 0
  BUSY READY FAULT SEEK DRQ CORR IDDEX ERROR
Error Register (Address 0x1F1): (check when ERROR==1)
  7 6 5 4 3 2 1 0
  BBK UNC MC IDNF MCR ABRT T0NF AMNF
  BBK = Bad Block
  UNC = Uncorrectable data error
  MC = Media Changed
  IDNF = ID mark Not Found
  MCR = Media Change Requested
  ABRT = Command aborted
  T0NF = Track 0 Not Found
  AMNF = Address Mark Not Found
```

The IDE interface looks like the above, and can be written to like so:

1. Wait for drive to be ready. (Register 0x1F7) should be READY and not
   BUSY.
2. Write parameters to command registers. Sector count, logical block
   address, and drive number should be written to command registers.
3. Start the I/O (issue read/write to command register, 0xF17).
4. Wait until drive status is READY and DRQ, write data to port.
5. Handle Interrupts
6. Handle errors by checking if the ERROR bit is on, read the error
   register.

Prev: [[35-a-dialogue-on-persistence]]
Next: [[37-hard-disk-drives]]
