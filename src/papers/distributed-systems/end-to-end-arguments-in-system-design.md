---
title: End to End Arguments in System Design
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Saturday, December 7th 2024, 8:45:59 pm
---

# End to End Arguments in System Design

The End to End argument states that some functions can only be completely and correctly implemented only at an application level.

[[Drawing 2023-03-10 19.56.56.excalidraw]]

## Reliable File Transfer

One example in the paper is Reliable File Transfer. The task is to move one file from Computer A to Computer B, where both computers are connected by a data link. Computer A chunks the file to send and then sends it over the data link, and Computer B receives the chunks, and recreates the file.

One way to create reliable transfer is to use TCP (with checksums) in the platform layer, and then hand the verified packets to Computer B. However, in Computer B, even if the packets are properly verified, the file on Computer A or Computer B could've become corrupt. Only the application layer can verify total failure detection and mitigation.
