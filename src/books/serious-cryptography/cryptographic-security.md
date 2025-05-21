---
title: "Cryptographic Security"
---

# Cryptographic Security

Prev: [randomness](randomness.md)
Next: [block-ciphers](block-ciphers.md)

It's important to calculate the security of a cryptographic system. How
much effort does it take to break it?

## Security in Theory vs Practice

In theory, a cipher is unconditionally secure if, given unlimited
computation time and memory, it would not be considered secure.

The one-time pad is unconditionally secure.

In practice, a cipher is secure if it cannot be broken within a
reasonable amount of time and reasonable resources, like memory,
hardware, budget, energy.

Consider a cipher, which has 128-bit security. In practice, $2^{128}$
security isn't breakable -- testing 100 billion keys per second, it
would take $10^{20}$ years, which is way too long.

Computation security is expressed with:

$t$, the limit on the number of operations an attacker carries out
$\epsilon$, the limit on the probability of a success.

So, a system is $(t, \epsilon)$ secure if an attacker, performing $t$
operations has less than an $\epsilon$ chance of breaking the scheme.

## Quantifying Security

A cipher is $t$-secure when an attack needs at least $t$ operations. So,
if it takes 1M operations to break a system, it has about 20 bits of
security. However, the security level isn't related to key size -- the
RSA algorithm with 1,024 bit elements provides less than 128-bit
security.

Also, keep in mind the cost of an operation. If you can do $2^{120}$
operations vs $2^{128}$ operations, the $2^{120}$ way is only better if
it's at most $2^8$ times as expensive to do.

## Calculating the Full Attack Cost

Bit security expresses the cost of the fastest attack against a cipher,
but other factors matter.

### Parallelism

Consider two attacks of $2^{56}$ operations:

1. The first one computes $2^{56}$ sequentially dependent operations.
2. The second one performs $2^{56}$ independent operations.

The second attack is much better, because you can parallelize
independent operations. So, if you could buy $2^{16}$ computers and run
the second algorithm, it will only take $2^{40}$ operations for each
computer, which is a nice speedup of 65,536x.

### Memory

The second factor is memory. An algorithm might take more memory
accesses compared to another, which slows its runtime.

### Precomputation

Precomputation attacks include computing a lookup table ahead of time
and using it later. The attack on 2G built 2TBs worth of tables over two
months, and then when breaking 2G's encryption, took a few seconds once
they recovered the ciphertext.

### Number of Targets

Say you want to break just one payload, and there are many payloads
(e.g. $2^{16}$). With $2^{128}$ bit security, since we only have to
break one of the keys, actually, there's only $2^{112}$ security.

## Choosing and Evaluating Security Levels

Generally a security level nowadays involves selecting between 128-bit
and 256-bit security levels.

Knowing that there are $2^{88}$ nanoseconds since the universe started,
you'd need several times the age of the universe for an attack to
succeed.

Assume you have a million targets and a million cores. Breaking 128-bit
security still requires 88 bits, which is still the age of the universe
in nanoseconds.

Since Moore's law says that computing efficiency doubles every two
years, we can think of this as a loss of 1 bit of security every two
years. If it costs $1000 to break some system, in 2 years it'll cost
$500, or you can break a system that is twice as hard for the same
amount.

In 80 years, we'll have 40 bits of fewer security than today.

Maybe quantum computers can break security for now, but if you want
security for 100 years, use 256-bit schemes, otherwise, 128-bit schemes
are reasonable.

## Achieving Security

There are two ways to check the security of a cryptosystem, either
theoretically (provable) or through failed attempts (probable).

### Provable Security

Generally to prove the security of a cryptosystem, you'd find an
equivalent problem and reduce it to that problem.

### Proofs relative to a Mathematical Problem

For example, the RSA cryptosystem uses the hard problem of factoring the
product of two prime numbers. The product of two prime numbers, `n =
pq`, is exponentially hard, and thus, infeasible for a large number, say
3000 bits long.

### Proofs Relative to Another Crypto Problem

You can also compare a cryptosystem to another cryptosystem, and prove
that you can only break one cryptosystem if you can break the other.
This is useful for symmetric ciphers.

### Caveats

Proofs aren't always correct, and implementations can be flawed. Also,
math problems can be easier than expected. Weak parameters and
implementation flaws can break RSA.

For example, Merkle and Hellman created a knapsack encryption scheme,
where an easy knapsack problem was transformed into a hard knapsack
problem, which is NP-hard. Since you'd have to decrypt the hard knapsack
problem, you'd think the algorithm was at least NP-hard, however, Shamir
found an attack in polynomial time that would break the scheme by
understanding its implementation.

### Heuristic Security

AES is not provably secure, however it's still used every day -- it
can't be proven to be secure, since it's not related to a math problem,
and doesn't compare well to other ciphers.

## Generating Keys

To encrypt something, you'll need keys. There are three ways:

1. Randomly, from a PRNG
2. From a password, where an algorithm transforms a password into a key
3. From a key agreement protocol

### Asymmetric Keys

Asymmetric keys generally represent a specific object type.

You give it a seed and then generate a private and public key.

## How things go wrong

Cryptographic security can go wrong in many ways:

In 2001, the Optimal Asymmetric Encryption Padding (OAEP) was
implemented on top of RSA, but it was proven incorrect 7 years later.

### Short keys

In 2015, researchers found that HTTPS sites supported public-key
cryptography of 512 bits instead of 2048 bits. 512 bit RSA keys provide
about 60 bits of security, which can be broken in less than a day now.
This required patching of OpenSSL.

Prev: [randomness](randomness.md)
Next: [block-ciphers](block-ciphers.md)
