---
title: security-and-https
---

And Https

# Security and HTTPS

## HTTP

HTTP is what the internet runs on.

HTTP is unencrypted, which allows people to intercept packets and read
them. This is a Man in the middle attack (MITM).

## Symmetric Encryption

- Symmetric Encryption involves using the same key to both encrypt and
  decrypt the data.
- One caveat means that this must be shared somehow previously.
- This is much faster than Asymmetrical Encryption, and is commonly
  implemented with AES.

### Advanced Encryption Standard (AES)

## Asymmetric Encryption

- Asymmetric Encryption relies on two keys, a public and private key
  to encrypt and decrypt data.
- Data encrypted with the public key can only be decrypted by the
  private key.
- A common algorithm is RSA, which uses two random prime numbers for
  the public and private key:

### RSA

```cpp
int x = 61, int y = 53;
int n = x * y;
// n = 3233.

// compute the totient, phi
int phi = (x-1)*(y-1);
// phi = 3120.

int e = findCoprime(phi);
// find an 'e' which is > 1 and is a co-prime of phi.
// e = 17 satisfies the current values.

// Using the extended euclidean algorithm, find 'd' which satisfies
// this equation:
d = (1 mod (phi))/e;
// d = 2753 for the example values.

public_key = (e=17, n=3233);
private_key = (d=2753, n=3233);

// Given the plaintext P=123, the ciphertext C is :
C = (123^17) % 3233 = 855;
// To decrypt the cypher text C:
P = (855^2753) % 3233 = 123;
```

## TLS

- TLS stands for Transport Layer Security, which is a security
  protocol that runs over HTTP to achievee secure communication
  online.

## SSL Certificate

- A trusted entity that signs digital certificates, (SSL Certificates)
  that are used to verify authenticity online.

## TLS Handshake

- The client sends a `client hello`---a string of random bytes---to
  the server.
- The server responds with a `server hello`---another string of random
  bytes---as well as its `SSL certificate`, which contains its
  `public key`.
- The client verifies that the certificate was issued by a
  `certificate authority` and sends `premaster secret`---yet another
  string of random bytes, this time encrypted with the server\'s
  public key---to the server.
- The client and the server use the client hello, the server hello,
  and the premaster secret to then generate the same
  `symmetric-encryption` session keys, to be used to encrypt and
  decrypt all data communicated during the remainder of the
  connection.

Prev: \[mapreduce](mapreduce.md) Next:
\[api-design](api-design.md)
