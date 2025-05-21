---
title: "Stream Ciphers"
---

# Stream Ciphers

Prev: [block-ciphers](block-ciphers.md)
Next: [hash-functions](hash-functions.md)

Stream ciphers generate pseudorandom bits from a key and encrypt a
plaintext by XORing it the generated bits.

## How Stream Ciphers Work

Stream ciphers take two values, a key and a nonce. The key must be
secret, and is 128 or 256 bits normally. The nonce doesn't need to be
secret, but it must be unique for each key, and is either a 64 or 128
bit value. It's also sometimes called the IV (initial value).

Stream ciphers compute the keystream as $KS = SC(K, N)$ and then
encrypts as $C = P \oplus KS$ and decrypts with $P = C \oplus KS$.

Prev: [block-ciphers](block-ciphers.md)
Next: [hash-functions](hash-functions.md)
