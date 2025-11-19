---
title: "An Algorithm For The Machine Calculation Of Complex Fourier Series"
pdf_url: "[[an-algorithm-for-the-machine-calculation-of-complex-fourier-series.pdf]]"
---
## Notes

This paper talks about reducing the time complexity of the discrete fourier transformation from $O(n^2)$ to $O(n\space log\space n)$.

The DFT has the formula:

$$
X_k = \sum_{n=0}^{N-1} x_n e^{-2\pi i kn / N}
$$
```python
def dft(x):
    """
    Naive DFT in O(n^2) time.
    """
    N = len(x)
    result = []
    for k in range(N):
        s = 0j
        for n in range(N):
            angle = -2j * math.pi * k * n / N
            s += x[n] * cmath.exp(angle)
        result.append(s)
    return result
```

The paper reduces this to $O(n\space log\space n)$ operations when $N$ is composite, so it can be written as $N = r_1r_2...r_m$. So, the indices can be re-expressed in factored form, and then turned into a sum that relies of fewer indices, and continue recursively. This divides and conquers the $O(n^2)$ algorithm into $O(n\space log\space n)$.

The Radix-2 FFT:

$$
E_k = \sum_{r=0}^{N/2-1} x_{2r} e^{-2\pi i kr / (N/2)},\quad
 O_k = \sum_{r=0}^{N/2-1} x_{2r+1} e^{-2\pi i kr / (N/2)}
$$

$$
X_k = E_k + e^{-2\pi i k / N} O_k,\quad
 X_{k+N/2} = E_k - e^{-2\pi i k / N} O_k,\quad 0 \le k < N/2
$$

```python
def fft(x):
    """
    Radix-2 FFT. O(n log n) time complexity if n is a power of 2.
    """
    N = len(x)
    if N <= 1:
        return x
    if N & (N - 1) != 0:
        raise ValueError("Length of input must be a power of 2 for this FFT implementation")

    # Recursive FFT on even and odd indices
    even = fft(x[0::2])
    odd = fft(x[1::2])

    result = [0j] * N
    for k in range(N // 2):
        twiddle = cmath.exp(-2j * math.pi * k / N) * odd[k]
        result[k] = even[k] + twiddle
        result[k + N // 2] = even[k] - twiddle
    return result
```
