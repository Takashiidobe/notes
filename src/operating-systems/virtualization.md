---
title: Virtualization
date created: Saturday, August 10th 2024, 2:38:48 pm
date modified: Tuesday, November 12th 2024, 8:31:16 pm
---
# Virtualization

Virtualization allows a computer to emulate another computer that may
not share the same characteristics as it -- imagine an x86 computer
running ARM software or vice-versa. If you can correctly emulate all the
instructions of the target architecture, you could hypothetically run
software unmodified on another system. However, without explicit
hardware support, this can be extremely slow. Luckily, most computers
support hardware instructions to aid in virtualization.

There are many approaches in software to virtualize hardware -- the JVM
is a good example, where you write instructions in some abstract
language which is translated into abstract bytecode and executed. Thus,
programs written in a VM language can target any language that supports
the VM.

You may also want to virtualize entire operating systems, instead of
just a programming language.

There are two main types of hypervisors, which run virtualized hardware.

## Type 1 Hypervisors

Type 1 Hypervisors run directly on the hardware, without running on top
of an operating system.

Type 1 Hypervisors run in privileged mode and hand out resources to
guest operating systems. Those VMs are isolated from each other and have
no direct access to the hardware, and ask the hypervisor for resources.

Some examples include Hyper-V and Xen.

## Type 2 Hypervisors

A Type 2 Hypervisor runs on top of an operating system, like Linux. So
the hypervisor is a userland application that allows for allocating VMs,
and it asks for resources from the underlying OS.

An example would be VirtualBox.

## Xen

One example of a type 1 Hypervisor is Xen. It runs a privileged process
in pid0, called Dom0 (Domain0). This process is a VM that starts when
the system boots, and has direct access to hardware.

Dom0 runs a modified version of linux and manages device drivers and
resources for the other VMs.

Dom0 can spawn User Domains (DomU)s, which are unprivileged VMs. Each
DomU is isolated from the other VMs.

Xen allows for paravirtualization, where the Guest OS is modified to
allow for better performance in virtualization, and also
Hardware-Assisted virtualization, which runs an unmodified version of a
given OS in a DomU, and uses specialized hardware instructions like AMD-V or
Intel VT-x to allow for better performance in virtualization.

## Intel's VT-x

VT-X is a set of extensions to support hardware virtualization. Some
instructions allow for the creation and management of VMs, the VMX
instructions, and Extended Page Tables, which allow for address
translation in a VM.

There are some other instructions, VT-d, which extends the
virtualization instructions by allowing the hypervisor to allocate
devices to VMs, process interrupts, and allow PCI passthrough, allowing
VMs to have near-native performance with hardware.
