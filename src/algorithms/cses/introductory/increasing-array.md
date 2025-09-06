---
title: Increasing Array
date created: Monday, July 21st 2025, 7:07:34 am
date modified: Monday, July 21st 2025, 8:10:13 am
---

# Increasing Array

Prev: [repetitions](repetitions.md) Next:
[permutations](permutations.md)

You are given an array of $$n$$ integers.  
You want to modify the array so that it is **increasing**, i.e., every element is at least as large as the previous element.  
On each move, you may increase the value of any element by one.  
What is the **minimum number of moves required**?

## Input

The first input line contains an integer $$n$$: the size of the array.  
The second line contains $$n$$ integers $$x_1, x_2, \ldots, x_n$$: the contents of the array.

## Output

Print the minimum number of moves.

## Constraints

$$1 \le n \le 2 \cdot 10^5$$  
$$1 \le x_i \le 10^9$$

## Example

**Input**

```
5
3 2 5 1 7
```

**Output**

```
5
```

## Answer

We want to turn any array into a non-decreasing array, so an array of $[4, 4, 4]$ would require 0 moves (no increments required). 

So, for every number in the list, we look back at our previous number. If we find that we are less than that number, we need to increment the count by that much and set our value equal to the previous number. At the end, we return the count.

```cpp
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    int n;
    std::cin >> n;
    std::vector<long long> a(n);
    for (auto& x : a) { 
	    std::cin >> x;
	}

    long long moves = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) {
            moves += a[i - 1] - a[i];
            a[i] = a[i - 1];
        }
    }

    std::cout << moves << '\n';
}
```

Prev: [repetitions](repetitions.md) Next:
[permutations](permutations.md)
