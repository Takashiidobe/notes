# First Bad Version

You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which returns whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

Example 1:

```
Input: n = 5, bad = 4
Output: 4
Explanation:
call isBadVersion(3) -> false
call isBadVersion(5) -> true
call isBadVersion(4) -> true
Then 4 is the first bad version.
```

Example 2:

Input: n = 1, bad = 1
Output: 1

## Solution

This is what `git bisect` does: It hunts for the troublesome commit in
$O(\log{} n)$ time (n being the number of commits).

This requires a binary search, where we check if the midpoint and its
previous commit are (false, true), i.e. the previous version is not bad,
but this one is.

If we don't find one where this is the case, we check if our midpoint
was a bad version. If it was, then we set the high to the previous
commit (since we know it was also bad).

Otherwise, we set the low point to the next commit, since we know this one
is good.

```python
class Solution:
    def firstBadVersion(self, n: int) -> int:
        low = 1
        high = n
        mid = (high + low) // 2

        while low <= high:
            mid = (high + low) // 2
            if isBadVersion(mid):
                if isBadVersion(mid - 1) == False:
                    return mid
                high = mid - 1
            else:
                low = mid + 1

        return mid
```