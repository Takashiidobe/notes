---
title: "Block Ciphers"
---

# Block Ciphers

Prev: [cryptographic-security](cryptographic-security.md)
Next: [stream-ciphers](stream-ciphers.md)

## What is a Block Cipher?

A block cipher consists of an encryption algorithm and a decryption
algorithm, where encryption is $C = E(K, P)$, and decryption is $P =
D(K, P)$.

For a block cipher to be secure, it should be a pseudorandom
permutation, so as long as the key is secret, the attacker can't learn
anything about the plaintext.

Block ciphers have to choose their block size and their key size. AES
has 128 bit blocks. Up to 512 bit blocks are good, because they fit in
registers.

64 bit blocks, like the ones in DES, are susceptible to birthday attacks
like Sweet32.

### Sweet32

Sweet 32 has been used to attack 3DES and blowfish in HTTPS. An attacker
that could monitor a long-lived connection between a client and a server
can recover HTTP cookies by capturing around 785GB of traffic.

The security of a block cipher, say DES, with a block size of 64 bits,
is reduced to 32GB ($2^{35}$).

128-bit AES block size requires 256 Exabytes ($2^{68}$) to break.

Sweet32 is a birthday attack, which exploits small block sizes and the
(Cipher Block Chaining mode) CBC.

CBC works by taking each plaintext block, and XORing the first block
with an IV, and then XORING each block with the previous one before
encrypting it. This makes the blocks dependent on each other, making
them independent and thus not easily parallelizable.

CBC is secure up to $2^{n/2}$ messages. Afterwards, a collision between
two ciphertext blocks is expected. A collision in the output means the
inputs are the same, which reveals the xor of two blocks. If you see a
fixed secret sent repeatedly, or some part of the plaintext is known,
you can use the xor of two blocks to figure out the secret.

As soon as $2^{S}$ blocks are encrypted, and $2^{t}$ blocks are
encrypted, and as long as $s + t \gteq n$ then the secret can be
cracked.

### The codebook Attack

Blocks can't be too small. Imagine a block size of 16 bits: to attack
this:

1. You would get all the ciphertexts corresponding to each plaintext
   block
2. Build a lookup table
3. To decrypt an unknown ciphertext block, look it up.

You only need 128KB for a 16-bit lookup table, or 32-bit blocks, 32GB.
With 64-bit blocks, you'd need to store 128EB, which is tough. For
128-bit blocks, far more.

## Constructing Block Ciphers

A block cipher is constructed by applying different rounds on the
plaintext to get the encryption key, and the inverse is applied to get
back the original plaintext.

The round functions are usually identical, but use different round keys.

### The Slide Attack and Round Keys

In a block cipher, no round should be identical to another round to
avoid the Slide Attack.

### Substitution-Permutation Networks

Confusion means the input undergoes complex transformations, and
diffusion means these transformations depend on all bits of the input.

### Feistel Schemes

DES is a Feistel scheme algorithm. It works as follows:

1. Split the 64-bit block into two 32-bit halves, L, R.
2. Set L to $L \oplus F(R)$ where F is a substitution round.
3. Swap the values of $L and R$
4. Repeat 15 times
5. Merge L and R into the 64-bit output block.

DES had a set of controversies, it had a short key-length, involvement
from the NSA, and suspicious substitution boxes that were used to
address a vulnerability that IBM and the NSA had known about, but did
not inform the public of (differential cryptanalysis). Shamir wrote
about this in the 80s, but it was known by NSA and IBM in the 70s, and
DES was hardened against it. It became public knowledge in the 90s that
DES was explicitly hardened by the NSA against it.

3DES was used before AES, but it only has 112-bit security, due to the
meet in the middle attack, where an attacker can create a lookup table
for one of the three rounds of 3DES and use that to nullify one of the
three rounds.

## AES

AES is the most used cipher in the world. It's also called Rijndael,
after its creators, Rijmen and Daemen. It was used to deprecate DES and
3DES.

### AES Internals

AES works on block sizes of 128-bits, with either 128-bit, 192-bit, or
256-bit keys. 128-bit works fine in most cases.

For 128-bit keys, it has 10 rounds of four steps:

1. AddRoundKey (XOR a round key to the internal state)
2. SubBytes (substitute a byte using a substitution box)
3. ShiftRows (Shift a row $i$ up $i$ positions, from 0 to 3)
4. MixColumns (Shift each column as well)

AES has a key schedule function, KeyExpansion.

- KeyExpansion deals with slide attacks
- AddRoundKey uses round keys for encryption
- SubBytes brings in nonlinear operations
- ShiftRows diffuses changes in every column
- MixColumns also helps with diffusion

To decrypt, AES uses its inverse function for each one. AddRoundKey is
unchanged.

## Implementing AES

You can implement AES with as little memory or as much memory usage as
you want -- the substitutions can be done with lookup tables in
software. However, x86_64 and ARM64 both provide AES instructions, so
most mobile phones and most desktop hardware support AES instructions in
hardware.

Intel hardware has supported AES-NI since 2010: An example encryption
call, where `xmm0` has the plaintext, `xmm5` to `xmm15` have the round
keys, and every instruction writes to `xmm0`. `pxor` XORs the first
round key before running the first round.

Keygen looks like the following:

```asm
.macro key_expand RCON DEST INV=0
    aeskeygenassist \RCON, %xmm0, %xmm1
    call key_combine
.if \INV
    aesimc %xmm0, \DEST
.else
    movaps %xmm0, \DEST
.endif
.endm

key_combine:
    pshufd $0b11111111, %xmm1, %xmm1
    shufps $0b00010000, %xmm0, %xmm2
    pxor   %xmm2, %xmm0
    shufps $0b10001100, %xmm0, %xmm2
    pxor   %xmm2, %xmm0
    pxor   %xmm1, %xmm0
    ret
```

With the actual key expansion

```asm
key_expand $1,   %xmm6
key_expand $2,   %xmm7
key_expand $4,   %xmm8
key_expand $8,   %xmm9
key_expand $16,  %xmm10
key_expand $32,  %xmm11
key_expand $64,  %xmm12
key_expand $128, %xmm13
key_expand $27,  %xmm14
key_expand $54,  %xmm15
```

```asm
pxor       %xmm5,  %xmm0
aesenc     %xmm6,  %xmm0
aesenc     %xmm7,  %xmm0
aesenc     %xmm8,  %xmm0
aesenc     %xmm9,  %xmm0
aesenc     %xmm10, %xmm0
aesenc     %xmm11, %xmm0
aesenc     %xmm12, %xmm0
aesenc     %xmm13, %xmm0
aesenc     %xmm14, %xmm0
aesenclast %xmm15, %xmm0
```

Decryption is the same, in inverse order with the decrypt instructions.

```asm
key_expand $1,   %xmm6,  1
key_expand $2,   %xmm7,  1
key_expand $4,   %xmm8,  1
key_expand $8,   %xmm9,  1
key_expand $16,  %xmm10, 1
key_expand $32,  %xmm11, 1
key_expand $64,  %xmm12, 1
key_expand $128, %xmm13, 1
key_expand $27,  %xmm14, 1
key_expand $54,  %xmm15, 0
```

```asm
pxor       %xmm15, %xmm0
aesdec     %xmm14, %xmm0
aesdec     %xmm13, %xmm0
aesdec     %xmm12, %xmm0
aesdec     %xmm11, %xmm0
aesdec     %xmm10, %xmm0
aesdec     %xmm9,  %xmm0
aesdec     %xmm8,  %xmm0
aesdec     %xmm7,  %xmm0
aesdec     %xmm6,  %xmm0
aesdeclast %xmm5,  %xmm0
```

Newer Intel computers also have VAES (vectorized AES instructions) for
more performance.

AES is as secure as a block cipher can be.

## Modes of Operation

### Electronic Codebook Mode (ECB)

Electronic Codebook mode (ECB) processes $P_1, P_2, ..., P_N$ in
parallel by processing each independently.

Marsh Ray said "Everybody knows ECB mode is bad ebcause we can see the
penguin:

![ECB Penguin](https://i.sstatic.net/AWg5i.jpg)

As you can see, the penguin's shape is pretty easy to see.

Identical ciphertext blocks reveal identical plaintext blocks to an
attacker.

### Cipher Block Chaining Mode (CBC)

Cipher Block Chaining Mode is like ECB, but you start by encrypting the
first block with an IV, and then every subsequent block is XORed the
previous encrypted block.

This makes each block dependent on all the previous blocks, so
encryption cannot be done in parallel.

The IV must be random.

### Message Padding

Since you won't always encrypt 16 bytes of data, you need to pad your
message. PKCS#7 is one way, shown below:

This pads by up to one block (in the case no padding was required).

| L mod 16 | Padding Length (P = 16 - (L mod 16)) | Padding Bytes                                                                     |
|:---------|:-------------------------------------|:----------------------------------------------------------------------------------|
| 0        | 16                                   | `0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10 0x10` |
| 1        | 15                                   | `0x0F 0x0F 0x0F 0x0F 0x0F 0x0F 0x0F 0x0F 0x0F 0x0F 0x0F 0x0F 0x0F 0x0F 0x0F`      |
| 2        | 14                                   | `0x0E 0x0E 0x0E 0x0E 0x0E 0x0E 0x0E 0x0E 0x0E 0x0E 0x0E 0x0E 0x0E 0x0E`           |
| 3        | 13                                   | `0x0D 0x0D 0x0D 0x0D 0x0D 0x0D 0x0D 0x0D 0x0D 0x0D 0x0D 0x0D 0x0D`                |
| 4        | 12                                   | `0x0C 0x0C 0x0C 0x0C 0x0C 0x0C 0x0C 0x0C 0x0C 0x0C 0x0C 0x0C`                     |
| 5        | 11                                   | `0x0B 0x0B 0x0B 0x0B 0x0B 0x0B 0x0B 0x0B 0x0B 0x0B 0x0B`                          |
| 6        | 10                                   | `0x0A 0x0A 0x0A 0x0A 0x0A 0x0A 0x0A 0x0A 0x0A 0x0A`                               |
| 7        | 9                                    | `0x09 0x09 0x09 0x09 0x09 0x09 0x09 0x09 0x09`                                    |
| 8        | 8                                    | `0x08 0x08 0x08 0x08 0x08 0x08 0x08 0x08`                                         |
| 9        | 7                                    | `0x07 0x07 0x07 0x07 0x07 0x07 0x07`                                              |
| 10       | 6                                    | `0x06 0x06 0x06 0x06 0x06 0x06`                                                   |
| 11       | 5                                    | `0x05 0x05 0x05 0x05 0x05`                                                        |
| 12       | 4                                    | `0x04 0x04 0x04 0x04`                                                             |
| 13       | 3                                    | `0x03 0x03 0x03`                                                                  |
| 14       | 2                                    | `0x02 0x02`                                                                       |
| 15       | 1                                    | `0x01`                                                                            |

### Ciphertext Stealing

Ciphertext stealing allows plaintexts of any bit length, not just bytes.
It's also not vulnerable to Padding Oracle Attacks, which is a big plus.

To implement it, you extend the last incomplete plaintext block with
bits from the previous ciphertext block and encrypting the resulting
block.

### Counter mode (CTR)

CTR turns a block cipher into a stream cipher. Instead of encrypting
just plaintext data, it encrypts blocks of a Nonce and an incrementing
counter.

If the nonce is $n$ bits, after $n / 2$ encryptions, and nonces, you'll
run into duplicates.

Since you're using an incrementing counter, it's parallelizable, which
is a big pro.

## How Things Can Go Wrong

### Meet-in-the-Middle Attacks

3DES is DES but run three times. You encrypt the block with a key,
$K_1$, then decrypt with key $K_2$, then encrypt with a key $K_3$.

If $K_1 = K_2$, the first two calls cancel themselves out, so this would
be single DES.

3DES actually only provides 112-bits of security, because of the MitM
attack.

2DES provides only $2^{57}$ bits of security, and it can be attacked
like so:

To do this attack, you would build a lookup table where $E(K_1,P)$ of
size $2^{56}$. For all values $2^{56}$ values of $K_2$, compute $D(K_2,
C)$, and check whether it appears in the lookup table.

Then, you have the pairs of $(K_1, K_2)$. You then verify that you've
found the right one by encrypting other plaintexts.

This allows you to verify the correct pair of keys with only $2^{57}$
operations.

For 3DES, you do the same thing except you have to go through 112-bits
of security.

### Padding Oracle Attacks

A Padding Oracle system behaves differently depending on whether or not
the padding in a CBC encrypted ciphertext is correct. Padding oracles,
thus, attack a padding system by recording which inputs return a success
or error by creating a bunch of ciphertexts and testing which ones are
correct.

To do this attack:

1. Pick a random block, $C_1$ and vary its last byte until the padding
   oracle accepts the ciphertext as valid. This should take 128 tries.
2. Find the previous value, $x[14]$, by setting $C_1[15]$ to $X[15]
   \oplus 02$ and finding the value that gives the correct 14th byte.
3. Repeat for all 16 bytes.

This thus requires about 2000 queries to recover 16 bytes of the
plaintext.

Prev: [cryptographic-security](cryptographic-security.md)
Next: [stream-ciphers](stream-ciphers.md)
