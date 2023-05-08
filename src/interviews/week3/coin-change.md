# Coin Change

You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.

Example 1:

```
Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
```

Example 2:

```
Input: coins = [2], amount = 3
Output: -1
```

Example 3:

```
Input: coins = [1], amount = 0
Output: 0
```

## Solution

This is a DP question -- generate an array of the minimum cost to create
every coin, and loop through the ranges of amount checking to see if
there's a cheaper way to create an amount.

Either we find a cheaper way, or there is no way to generate the amount,
in which case, we return -1

```python
class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        dp = [0] + [float('inf')] * amount

        for a in range(1, amount + 1):
            for coin in coins:
                if a - coin >= 0:
                    dp[a] = min(dp[a-coin] + 1, dp[a])

        return -1 if dp[amount] == float('inf') else dp[amount]
```
