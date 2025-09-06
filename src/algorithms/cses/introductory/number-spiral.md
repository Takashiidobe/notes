---
title: Number Spiral
date created: Monday, July 21st 2025, 7:07:34 am
date modified: Tuesday, July 22nd 2025, 7:49:18 am
---

# Number Spiral

Prev: [permutations](permutations.md) Next:
[two-knights](two-knights.md)

A **number spiral** is an infinite grid whose upper-left square has number 1.  
Here are the first five layers of the spiral:

Your task is to find out the number in **row** $y$ and **column** $x$.

## Input

The first input line contains an integer $t$: the number of test cases.  
After this, there are $t$ lines, each containing two integers $y$ and $x$.

## Output

For each test case, print the number in row $y$ and column $x$.

## Constraints

$$1 \le t \le 10^5$$  
$$1 \le y, x \le 10^9$$

## Example

**Input:**

```
3
2 3
1 1
4 2
```

Output:

```
8
1
15
```

## Answer

Case 1: $a > b$ (we're below the diagonal)

   If $a$ is even → the spiral fills bottom to top, so value decreases as $x$ increases.
   
   $$ans=a^2−b+1$$

   If $a$ is odd → spiral fills top to bottom, so value increases as $x$ increases.
   
   $$ans=(a−1)^2+b$$

Case 2: $a < b$ (we're right of the diagonal)

   If $b$ is even → spiral fills left to right, increasing in $y$. 
   
 $$ans= (b−1)^2 +a$$
  If $b$ is odd → spiral fills right to left, decreasing in $y$. 
  
  $$ans=b^2−a+1$$

```cpp
#include <iostream>

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        long long a, b;
        std::cin >> a >> b;
        long long ans;

        if (a > b) {
            if (a % 2 == 0) {
                ans = a * a - b + 1;
			} else {
                ans = (a - 1) * (a - 1) + b;
			}
        } else {
            if (b % 2 == 0) {
                ans = (b - 1) * (b - 1) + a;
			} else {
                ans = b * b - a + 1;
			}
        }

        std::cout << ans << '\n';
    }
}
```


Prev: [permutations](permutations.md) Next:
[two-knights](two-knights.md)
