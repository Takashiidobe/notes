---
title: Use Linux
date created: Wednesday, May 21st 2025, 7:46:44 am
date modified: Sunday, July 6th 2025, 2:41:25 pm
---

# Use Linux

## Context

I have a lot of computers. I own a phone, a tablet, a laptop, a mini-pc,
desktop, and servers in the cloud, all of which run linux. Linux works
well on many architectures and on very weak devices to high powered
devices.

1. Stability
2. Correctness
3. Maintainability
4. Portability
5. Expressiveness

## Stability

Linux (the kernel) is very stable. Linus has repeated that linux doesn't
break userspace from the kernel. To keep backwards compatibility, this
involves making different versions of the same syscall and supporting
them. In exchange, the kernel itself is painless to upgrade.

Stability is also important in other ways -- linux being just the kernel
means you're not bound to userspace + kernel changes the way you are
with Windows or MacOS, with most of those responsibilities being shunted
out to linux distributions. If I stop agreeing with the values of a
specific linux distribution, I can just choose a new one, or compile my
own operating system, something impossible to do for MacOS or Windows.

The more interesting comparison comes against the BSDs -- Linux has far
superior driver support and far better userspace software support.

## Portability

It's fairly easy to run modern linux (6.X) on the computer I used as a
child (an i586). For the other popular desktop operating systems (MacOS,
Windows) the oldest computer you run the latest OS on would be about 15
years old, instead of 30.


