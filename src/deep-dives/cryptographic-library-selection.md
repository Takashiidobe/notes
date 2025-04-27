# Cryptographic Library Selection

To build a secure web app, use a battle-tested library. Don't roll your
own crypto. The library should have secure supported algorithms,
compliance with standards, performance, be secure, and be high-level.

## Implementation Flaws

Some common implementation flaws:

1. Insecure modes, missing auth + using ECB, reusing IVs/nonces, or
   encrypting without a message tag leads to trivial attacks. Encryption
   should always be authenticated (like AES-GCM, ChaCha20-Poly1305) with
   random nonces.

2. Deprecated algorithms should not be supported. MD5, SHA-1, DES, 3DES,
   RC4, or PKCS#1 are all broken. Use SHA-2/3, AES, and modern padding
   algorithms.

3. Poor randomness: Use cryptography quality entropy, rotate your keys,
   and never reuse keys.

4. Side channel leaks: variations in timing or error messages can leak
   secret data. Padding oracles and timing attacks have been used to
   compromise TLS.

5. API Misuse: The API to use should be high-level such that it is
   impossible to misuse, like AES+CBC without HMAC should be impossible.

6. Implementation bugs: The library should have a small surface for
   fewer possible bugs.

## Some Libraries to use

- OpenSSL: while OpenSSL has lots of vulnerabilities, it is FIPS
  compliant, and provides most algorithms.
- LibreSSL: Not FIPS compliant, it is a fork of OpenSSL to modernize the
  codebase and drop legacy algorithms. Google forked it for android, and
  made BoringSSL, with even fewer features.
- Libsodium: A high-level crypto library based on the low-level NaCL
  lib. It supports modern primitives, secret key authentication, public
  key encryption, signatures, high quality RNG, password hashing. It
  lacks support for RSA because it prefers ECC.
- Mbed TLS: A crypto library by ARM. It has AES, RSA, ECC, TLS clients +
  servers, and is mainly for embedded devices. Supports FIPS.
- Tink: A modern cryptography suite by Google. Kind of like libsodium,
  but it has more APIs and is mainly for key management.
