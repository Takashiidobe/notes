---
title: binary-exponentation
---

Exponentiation\"

Binary Exponentiation allows us to calculate an exponent in O(log n)
exponentiations, instead of O(n).

Take 2 \^ 13:

We turn 13 into its binary representation:

1101

This corresponds to (2 \^ 8) \* (2 \^ 4) \* (2 \^ 1) or 8192.

So, let\'s break it down into a formula:

if n == 0: a \^ n == 1 if n \> 0 and n is even: a \^ n == a \^ (n / 2)
\^ 2 if n \> 0 and n is odd: a \^ n == a \^ (n - 1 / 2) \* a

And in a recursive formula:

```cpp
int binpow(int a, int b) {
  if (b == 0) return 1;
  int res = binpow(a, b / 2);
  if (b % 2 == 1) return res * res * a;
  else return res * res;
}
```

Or iteratively:

```cpp
int binpow(int a, int b) {
  int res = 1;
  while (b > 0) {
    if (b % 2 == 1) res = res * a;
    a = a * a;
    b >>= 1;
  }
  return res;
}
```
