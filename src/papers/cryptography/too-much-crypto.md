---
title: "Too Much Crypto"
pdf_url: "[[too-much-crypto.pdf]]"
---
## Notes

This paper makes the point that symmetric cryptography primitives tend to err on the side of caution and use many more rounds than they need to.

It advocates for fewer rounds for AES, BLAKE, ChaCha, and SHA-3 (Keccak).

In 2025, how did it hold up?

https://bfswa.substack.com/p/6-years-after-too-much-crypto

## AES

9 rounds instead of 10. The best practical attack works on 6 rounds, so 10 is fine. Since AES is hardware accelerated anyway, this doesn't matter.

## Blake2

Blake2 had 12 rounds, Blake2b had 8 rounds, and Blake2s had 7 rounds. Blake3 has 7 rounds. No attacks are even close.

## Chacha

Chacha is most popular in its 20 round form (ChaCha20). However, JP proposes ChaCha8, 8 rounds. There's an attack on ChaCha7, where an attack would require $2^{148}$ operations. This is far out of current compute.

## SHA-3

The best attack breaks 5-rounds. JP proposed 10 rounds instead of 24. There's nowhere near enough progress to break this.