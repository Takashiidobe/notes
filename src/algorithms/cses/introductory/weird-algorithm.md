---
title: Weird Algorithm
date created: Monday, July 21st 2025, 7:07:34 am
date modified: Monday, July 21st 2025, 7:43:04 am
---

# Weird Algorithm

Next: [missing-number](missing-number.md)

You are given a positive integer $n$.  
If $n$ is even, set $n \leftarrow \dfrac{n}{2}$;
if $n$ is odd, set $n \leftarrow 3n + 1$.  
Repeat this process until $n = 1$.

For example, the sequence for $n = 3$ is

$$3 \;\rightarrow\; 10 \;\rightarrow\; 5 \;\rightarrow\; 16 \;\rightarrow\; 8 \;\rightarrow\; 4 \;\rightarrow\; 2 \;\rightarrow\; 1.$$

Your task is to print every value of $n$ that appears during the algorithm.

## Input

The only input line contains an integer $n$.

## Output

Print a single line containing all values of $n$ produced by the algorithm, separated by spaces.

## Constraints

$$1 \le n \le 10^6$$

## Answer

This is the collatz conjecture.

```cpp
#include <iostream>

int main() {
  long long n;

  std::cin >> n;
  std::cout << n << ' ';
  
  while (n > 1) {
    n = n % 2 == 0 ? n / 2 : (n * 3) + 1;
    std::cout << n << ' ';
  }
}
```

Next: [missing-number](missing-number.md)
