---
title: Multicast
---

# Multicast

Multicast allows you to send the same message to multiple clients at the same time. TCP assumes there is one sender and one receiver (unicast). This makes it so the sender has to send the same data multiple times to different clients, and this requires copying.

With UDP, you can send to one client, or a virtual participant, which clients can assume are groups and join accordingly, and the hardware will take care of copying.
