---
title: "Randomness"
---

# Randomness

Prev: [encryption](encryption.md)
Next: [cryptographic-security](cryptographic-security.md)

Randomness is critical in building cryptographic systems.

## Randomness as a Probability Distribution

A randomized process is characterized by a probability distribution,
which shows the outcomes of a randomized probability.

## Entropy

Entropy is a measure of the uncertainty of the system. The higher the
entropy, the less is known about the system. Entropy can be computed as
the negative sum of all probabilities multiplied by their logarithm
Entropy can be computed as the negative sum of all probabilities
multiplied by their logarithm.

$$ H(P) = -\sum_{i=1}^{n} p_i \log_2(p_i) $$

$$ H(P) = -2^{128} \cdot \frac{1}{2^{128}} \log_2\left(\frac{1}{2^{128}}\right) $$
$$ H(P) = -\log_2\left(2^{-128}\right) $$
$$ H(P) = -(-128) \log_2(2) $$
$$ H(P) = 128 $$

So, entropy is maximized when the distribution is uniform, and is
minimized when the distribution is more certain. For a fair coin with
1/2 heads and 1/2 tails, we get two bits of entropy if we toss it twice
(since it's unpredictable twice).

$$ H(P) = -\sum_{i=1}^{2} \frac{1}{2} \log_2\left(\frac{1}{2}\right) $$
$$ H(P) = -\left[ \frac{1}{2} \log_2\left(\frac{1}{2}\right) + \frac{1}{2} \log_2\left(\frac{1}{2}\right) \right] $$
$$ H(P) = -\left[ \frac{1}{2} (-1) + \frac{1}{2} (-1) \right] $$
$$ H(P) = -(-1) $$
$$ H(P) = 1 $$

$$ H(P) = -\sum_{i=1}^{2} p_i \log_2(p_i) $$
$$ H(P) = -\left[ \frac{1}{4} \log_2\left(\frac{1}{4}\right) + \frac{3}{4} \log_2\left(\frac{3}{4}\right) \right] $$
$$ H(P) = -\left[ \frac{1}{4} (-2) + \frac{3}{4} (\log_2(3) - 2) \right] $$
$$ H(P) = -\left[ -\frac{2}{4} + \frac{3}{4} \log_2(3) - \frac{6}{4} \right] $$
$$ H(P) = -\left[ -2 + \frac{3}{4} \log_2(3) \right] $$
$$ H(P) = 2 - \frac{3}{4} \log_2(3) = 0.81 $$

So, we lose some entropy when the coin toss is more biased.

## Randomness and PRNGs

Cryptosystems need randomness to be secure. There are two needs:

1. A source of entropy, to provide to the RNG.
2. A cryptographic algorithm to produce high-quality random bits from
   the source of entropy.

The best entropy comes from analog sources. However, these aren't always
available. They can also source entropy from an OS by drawing from
devices and user input. They can be manipulated by an attacker, but
they're generally useful -- with the caveat that they don't produce many
bits.

Thus, PRNGs address the problem of low bit count by using a few bits to
generate a lot of bits.

## How PRNGs work

PRNGs receive random bits from an RNG at regular intervals and uses them
to update the contents of its entropy pool.

To generate more bits, the PRNG runs a DRBG algorithm that turns some
bits from the pool into a longer sequence.

PRNGs should guarantee backtracking resistance (forward secrecy),
meaning previously generated bits are impossible to recover, and
prediction resistance (backward secrecy) that future bits should be
impossible to predict.

For prediction resistance, the PRNG must get new random bits. For
backtracking resistance, transformations performed when updating the
state should be irreversible.

### Fortuna

Fortuna is a PRNG used in windows, macOS and iOS.

It has 32 entropy pools, so that $P_i$ is used every $2^i$ reseeds.

A key, and a counter which are 16 bytes.

`init()` sets K, C, and the entropy pools to 0.

`refresh(R)` appends the data R to one of the entropy pools.

`next(N)` updates K using data from a pool. The N bits requested are
produced by encrypting C with K as a key.

## Mersenne Twister (MT)

The Mersenne Twister is a noncryptographic PRNG used often. It has 624
32-bit words, in an array. It then sets them, and for every iteration,
it adds a new word to the array, with the equation:

$$ x_i = x_{(i + m) mod n} \oplus ((x_i^u | x_{(i+1) mod n}^l) A) $$

## Linearity Insecurity

An XOR of bits is called a linear combination, because

$$ X \oplus Y \oplus Z $$

while

$$ x \and Y \oplus Z $$

is not.

Linear operations are more predictable -- they lead to short equations,
which are easier to solve with linear algebra. Nonlinear equations have
equations of exponential size, which are harder to solve.

## Real-World PRNGs

### `/dev/urandom`

In Linux `/dev/urandom` is used to generate random bits. You should make
sure to check for errors, so you always get enough randomness.

In Linux, before 5.17, `/dev/random` used to be blocking if the kernel
thought the quality of the entropy was not high enough. This was a bad
idea, because `/dev/random` ran out of entropy quickly, blocking
applications that used it.

After 5.17, BLAKE2 is used instead of SHA-1, and is more reliable.

### Intel Secure Key (Hardware PRNG)

Intel introduced a hardware PRNG in 2012 with Ivy Bridge. It's accessed
through the `RDRAND` assembly instruction, which takes a register of 16,
32, or 64 bits and then writes a random value. It sets the carry flag to
1 if the operation was successful, so that needs to be checked.

There's also `RDSEED` which returns random bits from the entropy
source, for seeding PRNGs.

## How things can go wrong

### Poor Entropy Sources

The SSL implementation of Netscape was computing 128-bit PRNG seeds like
so:

```python
global variable seed;

RNG_CreateContext()
    (seconds, microseconds) = time of day; /* Time elapsed since 1970 */
    pid = process ID;  ppid = parent process ID;
    a = mklcpr(microseconds);
    b = mklcpr(pid + seconds + (ppid << 12));
     seed = MD5(a, b);

mklcpr(x) /* not cryptographically significant; shown for completeness */
    return ((0xDEECE66D * x + 0x2BBB62DC) >> 1);

MD5() /* a very good standard mixing function, source omitted */
```

The `RNG_CreateContext()` call is insecure -- PIDs and microseconds are
guessable, because there are only $2^{20}$ microseconds, or about 20
bits of entropy, and each PID only has 15 bits of entropy, with some
overlap, so 47-bits of entropy are used to generate a 128-bit seed,
which should have about 128 bits of entropy.

### Insufficient Entropy at Boot Time

In 2012, researchers harvested public keys from TLS certificates and SSH
hosts. They found that a handful of systems had identical public keys,
and very similar keys (RSA keys that shared one prime factor), where
normally the two prime factors should be distinct.

This is bad, because if you have one shared prime factor, you can
recover the other one by computing the GCD of the original number.

### Noncryptographic PRNG

Mediawiki, which runs wikipedia, was found to have noncryptographic
PRNGs for temporary passwords and security tokens:

Mersenne twister values can be predicted, so this is incorrect.

### Sampling bug with Strong Randomness

Cryptocat was a chat program for secure communication.

It had a random implementation like this:

```js
function random() {
    var x, o = '';
    while (o.length < 16) {
        x = state.getBytes(1);
        if (x[0] <= 250) {
            o += x[0] % 10;
        }
    }
    return parseFloat('0.' + o);
}
```

There's an off by one error, where `<=` should be `<`. This means that
it's slightly more likely to get a modulo of 0, so the distribution of
bytes is 0-250 instead of 0-249, and thus, x has a slightly higher
chance of being 0 than any other number.

Prev: [encryption](encryption.md)
Next: [cryptographic-security](cryptographic-security.md)
