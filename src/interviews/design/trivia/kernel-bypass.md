# Kernel Bypass

Kernel Bypass involves avoiding the kernel for system calls, and bringing those system calls to userspace. The most popular example is networking -- instead of using the linux network kernel, a fast userspace one is important.

Solarflare sells a userspace TCP stack (OpenOnload) for use with their NICs.

## Why Do Kernel Bypass?

Currently, the Linux Kernel can process 1M requests per minute. For more, you'll need configuration.

## Kernel Bypassing Userspace Networking

A Userspace TCP stack is more efficient, but is hard to debug (Linux tools won't work, so it's up to the creator of the library to provide debugging tools).

A full kernel bypass has the best performance, but worst debuggability (no SSH!)

A partial kernel bypass works, where you get some extra performance off of a SolarFlare NIC by bypassing one RX queue.

## How do you Kernel Bypass?

To Kernel Bypass, `Packet_mmap` dodges the two system calls that `AF_PACKET` uses, and sets up a ring buffer to send or receive packets (much like `io_uring`).

Unfortunately `Packet_mmap` isn't that fast, as packets still go through the kernel.

Other networking frameworks, like DPDK, Netmap, or Snabbswitch take over the entire network card, which makes debugging harder.

## Solarflare's EF_VI

Solarflare's EF_VI supports OpenOnload, which `LD_PRELOAD`s network syscalls of the running program. Then it has its own RX queue, hidden from the kernel, which, once a filter rule is set up, packets can be routed to it, bypassing the kernel, and getting that sweet 15M packet line speed.
