# Best Time to Buy and Sell Stock

You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

Example 1:

```
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
```

Example 2:

```
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.
```

## Solution

To find the maximum profit from being able to buy and sell a stock, we
keep track of the minimum number so far, and the extractable profit
(taking each price we see, subtracting it from the smallest price we
saw, and then setting max profit to our profit if its larger than before).

At the end, we return that value.

```python
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        max_profit = 0
        min_so_far = prices[0]

        for price in prices[1:]:
            profit = price - min_so_far
            max_profit = max(max_profit, profit)
            min_so_far = min(min_so_far, price)

        return max_profit
```
