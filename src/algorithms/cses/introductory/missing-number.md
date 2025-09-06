---
title: Missing Number
date created: Monday, July 21st 2025, 7:07:34 am
date modified: Monday, July 21st 2025, 7:47:13 am
---

# Missing Number

Prev: [weird-algorithm](weird-algorithm.md) Next: [repetitions](repetitions.md)

You are given all the numbers between $1, 2, \ldots, n$ **except one**.  
Your task is to find the **missing number**.

---

## Input

- The first input line contains an integer $n$.
- The second line contains $n-1$ distinct integers between $1$ and $n$ (inclusive).

## Output

Print the missing number.

## Constraints

$$2 \le n \le 2 \cdot 10^5$$
## Example

**Input**

```
5
2 3 1 5
```

**Output**

```
4
```

## Answer

The total sum of a sequence of $n$ numbers from 1 to $n$ is $n(n + 1)/2$. We can thus take the length of the sequence provided, and apply the previous formula to it to get its sum.
Afterwards, we take the sum of the provided numbers, and subtract the sum from the previous number we got, which returns us the missing number.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> nums(n - 1);
    for (int& x : nums) {
        cin >> x;
    }

    long long total = 1LL * n * (n + 1) / 2;
    long long sum = accumulate(nums.begin(), nums.end(), 0LL);

    cout << total - sum << '\n';
    return 0;
}
```

Prev: [weird-algorithm](weird-algorithm.md) Next: [repetitions](repetitions.md)
