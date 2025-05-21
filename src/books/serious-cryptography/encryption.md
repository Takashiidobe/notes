---
title: "Encryption"
---

# Encryption

Next: [randomness](randomness.md)

This chapter talks about the basics of symmetric encryption.

Plaintext: payload
Ciphertext: encrypted payload
encryption: payload -> encrypted payload
decryption: encrypted payload -> payload

## Classical Ciphers

Classical Ciphers predate computers, so they work on strings.

### Caesar Cipher

The Caesar Cipher supposedly comes from Julius Caesar. It works by
shifting each message down three positions, wrapping around if
necessary.

```
ZOO -> CRR,
FDHVDU -> CAESAR
```

This is easy to break, and even if you make the shift secret, it's still
trivially breakable -- there are only 25 possible shifts.

### The Vignere Cipher

The Vignere Cipher is similar to the Caesar Cipher, but it has a key.

For example, `DUH` would mean to shift each letter by 3, 20, and 7. Thus,
`CRYPTO` would encrypt to `FLFSNV`.

This is more secure, but still has pitfalls. `THEY DRINK THE TEA` would
turn into `WBLBXYLHRWBLWYH`. Note that `WBL` appears twice, which means
that the same three letter word appears in the payload twice. This
allows the analyst to know that the key is either nine or a value that
divides 9, and then guess some common three letter words, such as `THE`,
and then deduce the key is `DUH`. Another way is to use frequency
analysis, noting that `E` is the most common letter in the English
alphabet, so if the most common letter in this payload is `X`, the
likely plaintext value would be `E`.

## How Ciphers work

Ciphers work by permutation and a mode of operation.

A permutation is a function that transforms an item into its unique
inverse.

A mode of operation uses a permutation to process messages of arbitrary
size. The Caesar cipher has a mode of operation of every letter, but the
Vignere Cipher uses a key for its mode of operation.

### The Permutation

To qualify as a permutation, you must have a substitution and an inverse
substitution, such that S -> S' and S' -> S, so you need two such
substitutions.

Permutations should have the following properties:

1. Be determined by the key
2. Different keys should result in different permutations
3. The permutation should look random

### The Mode of Operation

The mode of operation of a cipher mitigates the exposure of duplicate
letters by using different permutations for the same letter, thus
combating frequency analysis. To make Vignere's cipher better, think
about encrypting a plaintext of the same length of the key -- you can't
glean any information about the plaintext, since the key is random.
However, you also can't use the key more than once -- imagine the key
`KYN`, with `TIE` and `PIE` as plaintexts -- their encryption of `DGR`
and `ZGR` leak that they both share the same last two letters.

So, a cipher must have a secure permutation and secure mode.

## The Perfect Cipher: The One-Time Pad

The one-time pad has perfect secrecy -- it's impossible to learn
anything about the plaintext with it.

The one time pad is, where C, P, and K have the same length.

$$ C = P \oplus K $$

We can decrypt by doing:

$$ P = C \oplus K $$

This is mathematically perfectly secure, but is inconvenient because it
can only ever be used once, and it requires a key as long as the
payload.

Assume if you use K to encrypt $P_1$ and $P_2$ into $C_1$ and $C_2$, you
can compute the XOR difference of both payloads.

$$ C_1 \oplus C_2 = (P_1 \oplus K) \oplus (P_2 \oplus K) = P_1 \oplus P_2 \oplus K \oplus K = P_1 \oplus P_2 $$

This allows an attacker to figure out the XOR difference of $P_1$ and
$P_2$, which allows frequency analysis to get a lead on figuring out the
plaintexts.

### One-Time Pad Security

The One-time pad is secure. Shannon proved that it is perfectly secure
as long as the key is as long as the payload.

As long as K is random, the resulting C looks as random as K to an
attacker, because XORing a fixed string with a random string results in
a random string, and the resulting ciphertext has a uniform
distribution, so all possible ciphertexts are possible, maximizing
secrecy.

## Encryption Security

Since the One-Time pad is impractical for use, we need to give up some
correctness for performance.

### Security Goals

Cryptographers define two criteria for what it means to learn about a
cipher's behavior:

1. Indinstinguisability (IND): Ciphertexts should be indistinguisable
   from random strings. If an attacker picks two plaintexts and then
   receives one of the ciphertexts, they shouldn't know which plaintext
   corresponds to the ciphertext they got.
2. Nonmalleability (NM): Given a ciphertext, it should be impossible to
   create another ciphertext whose plaintext is related.

## Asymmetric Encryption

Asymmetric Encryption involves two keys: a public and a private key. The
public key should be considered publicly available, however, the
decryption key should remain secret and is called a private key.

The public key can be computed from the private key, but not vice-versa.

## Applications of Ciphers

### Authenticated Encryption

Authenticated Encryption is a form of symmetric encryption that returns
an authentication tag along with the ciphertext.

So, $AE(K, P) = (C, T)$. Decryption takes the inverse; $AE(C, T) = P$
and only returns the P if it verifies that T is a valid tag for the
plaintext-ciphertext pair.

The tag ensures the integrity of the message.

### Format Preserving Encryption

Format preserving encryption creates ciphertexts that have the same
format as the plaintext.

### Fully Homomorphic Encryption

A homomorphism in group theory is a structure-preserving mapping between
two algebraic structures. In this case, an operation on the plaintext
does the same thing to the ciphertext.

$$ D(f(E(m_1), ..., E(m_n))) = f(m_1, ..., m_n) $$

A good use case for this would be cloud providers -- you may want to
store some valuable data on the cloud. You can encrypt it before storing
it again, but this is cumbersome because you need to encrypt a whole
file before storing it on the cloud again. With Fully Homomorphic
Encryption, you could store it encrypted once, apply any mutations you
want to it, without the cloud provider knowing the original data or what
the changes are doing.

### Searchable Encryption

Searchable encryption allows searching over an encrypted database
without leaking the search terms.

### Tweakable Encryption

Tweakable encryption is like basic encryption, but provides a random
value that makes the encryption unreplicable by other customers.

## How Things Go wrong

### Weak Ciphers

The first attack involves 2G. Encryption in 2G used a cipher called
A5/1, which allowed intercepting calls.

A5/1 uses a combination of LSFRs. They could precompute a large table
(in the order of TBs) for a subset of possible initial states of the
LSFRs.

Then, during the attack, the attacker would capture the ciphertext, and
then index into their precomputed table, to find matching LSFR states.

Then, they could try to recover the entire key and decrypt the
conversation.

### Wrong Model

Padding oracle attacks are when attackers learn whether a ciphertext
conforms to a required format.

A ciphertext is only valid if its plaintext has the proper padding. So,
attackers would send a ciphertext to some system and observe whether it
threw an error. Because of this, they were able to decrypt ciphertexts
without knowing the key.

Next: [randomness](randomness.md)
