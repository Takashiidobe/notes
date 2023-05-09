---
title: "Bit Hacks"
---

# Bit Hacks

Prev: [bentley-rules-for-optimizing-work](bentley-rules-for-optimizing-work.md)
Next: [assembly-language--computer-architecture](assembly-language--computer-architecture.md)

## Binary Representation

Let $x = \{x_{w-1}, x_{w-2}, \dots, x_{0}\}$ be a $w$-bit computer word.

So: `0b10010110` would represent 128 + 16 + 4 + 2 or 150 if it was unsigned.

The signed integer (two's complement) would be:

$$x = (\displaystyle \sum_{k=1}^{w-2}x_{k}2^k) - x_{w-1}2^{w-1}$$

So: `0b10010110` would be -128 + 16 + 4 + 2 or -106.

Thus, `0b00000000` would be 0.

And `0b11111111` would be -1.

Thus, `x + ~x = -1`, or `-x = ~x + 1`.

Prev: [bentley-rules-for-optimizing-work](bentley-rules-for-optimizing-work.md)
Next: [assembly-language--computer-architecture](assembly-language--computer-architecture.md)
