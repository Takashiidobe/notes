# How TLS Works

TLS encrypts traffic on the internet, so sensitive messages can't be
read by a man in the middle, or someone spoofing a domain.

To view TLS handshake information, try this command:

`openssl s_client -connect google.com:443 -tls1_2`

An example TLS cipher would be `tls_ecdhe_rsa_with_aes_128_gcm_sha256`.

1. `TLS` is the name of the protocol, which can be 1.1, 1.2, or 1.3.
The version dictates the ciphers that the client or server support.

2. `ECDHE` is `Elliptic Curve Diffie-Hellman Ephemeral`, which is the
   key exchange mechanism. Note that we can't use raw RSA or raw DH over
   the internet due to a possible MITM attack. Ephemeral means that
   temporary keys are used for each session, to provide forward secrecy.

3. `RSA` is the authentication algorithm, used to authenticate the
   server's public key matches up with the domain's public key provided
   in its cert.

4. `AES_128_GCM` is AES in 128-bit block mode in Galois Counter mode.

5. `SHA256` is the hash algorithm used to HMAC the data.

A TLS handshake might look like this:

1. The client sends a `Client Hello` message to the server, which has
the max TLS version the client supports and a random number, and a
cipher suite. The random number prevents replay attacks.

2. The server reads the client's message and sends a `Server Hello`
   message, which contains a chosen TLS version, a random number, and a
   chosen cipher suite. If there's no match in ciphers, a TLS alert
   message is sent, and the handshake fails.

3. The server sends over its certificate with a public key, and also the
   client and server select the generator and large number to use in
   Diffie-Hellman key exchange, and a digital signature, which is the
   previous messages concatenated together, hashed with the hashing
   algorithm, and then signed with the private key of the server.

4. The client now has the public key on the certificate, and checks with
   their certificate authority to make sure it's correct. Then, it decrypts the
   digital signature from the server by using the public key on the
   certificate.

5. The client then has to verify that the server has the private key. It
   can do this by generating a random number, called the pre-master
   secret and encrypting it with the server's public key. Only the server can
   decrypt it with its private key.

6. The server decrypts the secret, and now the server and client have
   the Client + Server random and the pre-master secret, which they can
   use to generate a shared secret using Diffie-Hellman, which becomes
   the ephemeral session key.

7. The client sends a ChangeCipherSpec message, to show that it is
   ready. This hashes all the records all up to that point, encrypts
   them with the session key, and sends it to the server. The server
   verifies this is correct with their key.

8. The server does the same thing, and the client verifies the server is
   correct.

9. The TLS handshake starts.
