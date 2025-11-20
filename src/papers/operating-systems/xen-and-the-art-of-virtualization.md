---
title: "Xen And The Art Of Virtualization"
pdf_url: "[[xen-and-the-art-of-virtualization.pdf]]"
---
Xen is a virtual machine monitor (VMM/hypervisor) for x86 that paravirtualizes resources to run with near-native performance and resource isolation.

## Requirements

The paper mentions 3 requirements for server-side virtualization:

1. Support many OS instances (100+ per box)
2. Host commodity OSes with unmodified userspace binaries
3. Provide strong performance and fault isolation.

Current full virtualization is awkward and has performance problems. Some instructions don't trap, and dynamic binary translation hurts perf.

Thus, Xen exposes a slightly different "virtual x86" and modifies the guest OS to fit to that interface.

## Paravirtualization

Xen runs in ring 0, guest kernels run in ring 1, and user processes run at ring 3.

The paper notes the interface is split into three:

1. Memory Management
	- Each guest OS manages hardware page tables itself.
	- Page tables are registered with Xen and made read-only.
	- Xen reserves a fixed region at the top of each address space for its own code/data to avoid TLB flushes
2. CPU and exceptions
	- The Guest OS runs at ring 1, and privileged instructions are replaced with hypercalls
	- Time is provided via Xen virtually
3. Device I/O 
	- Device I/O moves through shared circular queues between Xen and each domain.
	- Zero-copy transfers via page pinning and DMA.
	- Events notify domains of completed I/O and other async conditions

## Dom0

- A special VM, Domain0 (Dom0) is created at boot. It can adjust CPU/memory usage of VMs, create/destroy domains, configure routing.

## Performance

- Overhead is about 0-10%, with many operations close to native.

## History

EC2 ran Xen as its hypervisor for over 10 years (from 2006-2017) until it changed to KVM (Nitro). Xen ended up being a godsend because VT-x wasn't popular yet in mainstream computers, and much better than the alternatives.