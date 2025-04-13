# TLS

Transport Layer Security (TLS) encrypts transmissions over the internet.
The two versions in common use are 1.2 (2008) and 1.3 (2018).

The main changes from 1.2 to 1.3 is supporting a narrower cipher suite,
fewer modes of operation, and some performance improvements.

## TLS 1.2

TLS 1.2 mainly used AES with 128-bit keys, along with Cipher Block
Chaining (CBC) or Galois Counter Mode (GCM). However, some deployments
had Triple DES (3DES), RC4, which are considered insecure.

To turn block ciphers like AES into stream ciphers, modes of operation
like CBC (which chained blocks with an initialization vector), or GCM.

Integrity protection was provided by Mac then encrypt, which was secure
in principle but error-prone in practice.

### Key Exchange

For key exchange, RSA and DH were supported. RSA exchange is
straightforward, where the client generates a pre-master secret,
encrypts it with the server's RSA public key and the server decrypts it,
but this has no forward secrecy, thus DH was preferred in practice.

Authentication was supported using an RSA or elliptic curve key.

## TLS 1.3

TLS 1.3 supports fewer ciphers (only 5)

- TLS_AES_256_GCM_SHA384
- TLS_CHACHA20_POLY1305_SHA256
- TLS_AES_128_GCM_SHA256
- TLS_AES_128_CCM_8_SHA256
- TLS_AES_128_CCM_SHA256

Every suite combines confidentiality and integrity.

There is also only DH key exchange, with support for X25519. RSA
signatures are allowed only for certificates, but not for key exchanges.

This makes forward secrecy mandatory and simplifies implementation.

This basically leaves two algorithms as the critical ones -- AES-GCM vs
ChaCha20-Poly1305.

AES has hardware instructions (AES-NI) on most hardware these days, and
so is hardware accelerated. ChaCha is an ARX (Addition, Rotation, XOR)
cipher that is efficient on software without hardware instructions.

This means that for lower-powered devices without hardware acceleration,
ChaCha20-Poly1305 is more performant, whereas AES is faster for hardware
accelerated devices.

As well, AES suffers from side-channel attacks if using lookup tables
(as is common in software), whereas ChaCha20-Poly1305 does not, as it is
simpler and its constant time implementation is not vulnerable to timing
attacks.
