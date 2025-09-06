---
title: Probabilistic Encryption
author:
  - "Shafi Goldwasser"
  - "Silvio Micali"
doi: "10.1145/800070.802212"
url: "https://doi.org/10.1145/800070.802212"
pdf_url: "[[Probabilistic encryption &amp;amp; how to play mental poker keeping secret all partial information.pdf]]"
is_oa: true
date created: Sunday, July 20th 2025, 10:34:11 am
date modified: Sunday, July 20th 2025, 10:34:28 am
---

# Probabilistic Encryption

Deterministic public key cryptosystems can be modeled like so:

`f` is the encryption function, where `M` is a message.

Therefore, the encrypted payload is `f(M)`, which is deterministic (I
can cheaply verify that the payload is `M` if I have `f(M)` and they are
equal.

This is prone to partial information leaks and other attacks -- let's
say you know that M is either `M1` or `M2`. In a deterministic
cryptosystem, you can apply `f` to `M1` and `M2` and figure out whether
`M` is `M1` or `M2` cheaply.

To mitigate against that, probabilistic encryption involves sending a
random number along with the payload, so the function looks like
`f(rand(), M)` which almost never encrypts the same payload the same.