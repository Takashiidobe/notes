---
title: design-a-video-upload-system-with-low-bandwidth
---
# Design a Video Upload System with Low Bandwidth

To handle the upload side of a video service, we can, on the client side, cut up the video into chunks and have the backend confirm that it's gotten each chunk and stitch up the video on its side.

There can be hashing + checksums in order to confirm that the upload worked as expected.