---
title: Permutations
date created: Monday, July 21st 2025, 7:07:34 am
date modified: Tuesday, July 22nd 2025, 7:19:33 am
---

# Permutations

Prev: [increasing-array](increasing-array.md)
Next: [number-spiral](number-spiral.md)

A permutation of integers $1, 2, \ldots, n$ is called **beautiful** if there are **no adjacent elements whose difference is 1**.  
Given $n$, construct a beautiful permutation if such a permutation exists.
## Input

The only input line contains an integer $n$.

## Output

Print a beautiful permutation of integers $1, 2, \ldots, n$.
If there are several solutions, you may print any of them.  
If there is no solution, print `NO SOLUTION`.

## Constraints

$$1 \le n \le 10^6$$

## Example 1

**Input**

```
5
```

**Output**

```
4 2 5 3 1
```

## Example 2

**Input**

```
3
```

**Output**

```
NO SOLUTION
```

## Answer

Note that a sequence can only be called beautiful if there are none with adjacent items. So, we need to be able to interleave a sequence of odd numbers with evens, since $[2, 4]$ is considered beautiful, as well as $[1, 3]$. Note that we can combine both of these as $[2, 4, 1, 3]$. So, we need to print out all the even numbers of the sequence, and then the odd numbers. 

However, note that $[1, 2]$ and $[1,2,3]$ do not follow this rule, since no matter how they're arranged, they always have at least one adjacent item with a difference of 1.

So, we apply this algorithm to sequences of at least length 4 only.

```cpp
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    if (n == 2 || n == 3) {
        std::cout << "NO SOLUTION\n";
        return 0;
    }

    std::vector<int> result;

    for (int i = 2; i <= n; i += 2)
        result.push_back(i);

    for (int i = 1; i <= n; i += 2)
        result.push_back(i);

    for (int x : result)
        std::cout << x << ' ';
    std::cout << '\n';
}
```


Prev: [increasing-array](increasing-array.md)
Next: [number-spiral](number-spiral.md)
