---
title: "Hamming Codes"
---

# Hamming Codes

Hamming codes are a way to guarantee error correction of faulty data in 1 bit flip out of a block of 16, and error detection for up to 2 bit flips in a block of 16.

The way it does that is by consuming $log(n)$ memory, where $n$ is the size of the block (in this case, 16). To do so, hamming codes reserve the 0th, 1st, 2nd, 4th, and 8th blocks as parity blocks.

The 1st block checks the parity of any blocks that have the first bit set,
The 2nd block checks the parity of any blocks that have the second bit set,
The 4th block checks the parity of any blocks that have the third bit set,
The 8th block checks the parity of any blocks that have the fourth bit set,
And the 0th block checks for the parity of the whole set of bits, which allows for error detection of up to 2 bits.

Hamming codes are perfect codes, which achieve the highest possible rate for codes.
