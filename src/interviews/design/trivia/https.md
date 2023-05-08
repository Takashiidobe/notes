# How does HTTPS work?

HTTPS works by encrypting communications between a client and a server, so any snoopers (Men in the Middle, or MITM) can't listen to communications between a client and a server.

This works via the following:

1. The client sends a ClientHello message. This contains the information that the server needs to connect to the client via TLS, including supported ciphers and the maximum TLS version supported.

2. The server responds with a ServerHello, which responds with the cipher chosen and the TLS version to use.

3. The server proves its identity to the client with a TLS certificate, which contains the certificate's public key, owner, timeframe, and domain that it is valid for. This is signed by a Certificate Authority which the client already trusts, so it can decrypt it using certificates already loaded onto its machine.

4. The client generates a random key to be used for a symmetric key exchange. It encrypts it using the agreed upon cipher, and the server's public key. The server decrypts this using its private key, and the handshake completes.

This works because we implicitly trust certain Certificate Authorities (CAs) on every device. Their certificates are embedded onto devices so said devices can be used for decryption.

Some problems include:

1. Misbehaving CAs (Symantec did this in the past, which lead to their certificates being removed from chrome). This means certain websites would become inaccessible for users, until servers changed their certs.

2. Weak Cryptography. RSA has been removed from TLS 1.3 (For good reason), to be replaced with more secure Diffie-Hellman curves. RSA-512 is supported on HTTPS, which can be cracked in less than $100 worth of AWS EC2 compute (FREAK). This is now impossible in TLS 1.3, because the server signs the payload deciding the cipher to use, which makes FREAK impossible.

3. Forward Secrecy: If a Server's Private key is leaked, all communications from the past can be unencrypted. To combat this, forward secrecy is used, which means after a key exchange of the server and client of public keys, each session can be encrypted with a different session key, which can be used to authenticate each other for one session.

## How did TLS 1.3 improve HTTPS?

- TLS 1.3 now requires one less round trip than TLS 1.2, as it only requires one round trip instead of two. If the user has connected to a website before, then it requires 0 round trips.
