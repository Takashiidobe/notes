---
title: Array Division
date created: Tuesday, August 22nd 2023, 7:25:12 pm
date modified: Sunday, July 27th 2025, 8:29:10 am
---

# Array Division

Prev:
[subarray-distinct-values](subarray-distinct-values.md)
Next: [sliding-median](sliding-median.md)

## Problem

You are given an array containing $n$ positive integers.  
Your task is to divide the array into $k$ subarrays so that the **maximum sum** in a subarray is as small as possible.

## Input

The first input line contains two integers $n$ and $k$: the size of the array and the number of subarrays in the division.

The next line contains $n$ integers $x_1, x_2, \ldots, x_n$: the contents of the array.

## Output

Print one integer: the maximum sum in a subarray in the optimal division.

## Constraints

$$
1 \le n \le 2 \cdot 10^5  
$$

$$
1 \le k \le n  
$$

$$
1 \le x_i \le 10^9
$$

## Example

**Input:**

```
5 3  
2 4 7 3 5
```

**Output:**

```
8
```

**Explanation:** An optimal division is [2,4],[7],[3,5] where the sums of the subarrays are 6, 7, and 8. The largest sum is 8.

## Answer

Note that a greedy approach works here, where we fix the largest sum, $X$ to some value, and then try to sum up to $k$ arrays where $max(sum(array_i))$ is <= $k$.

The minimum number is the maximum of the array, and the highest value is the sum of all numbers in the given array.

we thus can binary search over the range of $[low, high]$ until we find the minimum answer which solves the problem, and return that.

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

bool can_divide(const vector<long long> &arr, int k, long long max_sum) {
  int count = 1;
  long long current_sum = 0;
  for (auto x : arr) {
    if (current_sum + x > max_sum) {
      count++;
      current_sum = x;
    } else {
      current_sum += x;
    }
  }
  return count <= k;
}

int main() {
  int n, k;
  cin >> n >> k;
  vector<long long> arr(n);
  for (int i = 0; i < n; ++i)
    cin >> arr[i];

  long long low = *max_element(arr.begin(), arr.end());
  long long high = accumulate(arr.begin(), arr.end(), 0LL);

  while (low < high) {
    long long mid = (low + high) / 2;
    if (can_divide(arr, k, mid)) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }

  cout << low << endl;
  return 0;
}
```

Prev:
[subarray-distinct-values](subarray-distinct-values.md)
Next: [sliding-median](sliding-median.md)
