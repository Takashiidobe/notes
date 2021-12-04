---
title: design-a-video-upload-system-with-low-bandwidth
---

A Video Upload System With Low Bandwidth

# Design a Video Upload System with Low Bandwidth

Users have to upload videos which are larger than 1GB. Network Bandwidth
is too low, and video uploads are dropped often. Design a solution to
address this issue.

Divide video into small chunks.

Tell backend how many chunks there are, the current chunk number, and
the hash of the chunk. The user will upload a chunk, and the backend can
verify that it was not tampered with by looking at the chunk hash.
