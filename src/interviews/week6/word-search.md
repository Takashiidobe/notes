# Word Search

Given an `m x n` grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

Example 1:

```
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true
```

Example 2:

```
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true
```

Example 3:

```
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false
```

## Solution

This requires no copies, but you can make a copy if needed.
Otherwise, make a copy of the board and mutate that.

```python
class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        m = len(board)
        n = len(board[0])
        word_len = len(word)

        def inbounds(y, x):
            return 0 <= y < m and 0 <= x < n

        def dfs(y, x, index):
            if index == word_len:
                return True
            if not inbounds(y, x) or board[y][x] != word[index]:
                return False
            tmp = board[y][x]
            board[y][x] = "#"
            res = any([
                dfs(y, x + 1, index + 1),
                dfs(y, x - 1, index + 1),
                dfs(y + 1, x, index + 1),
                dfs(y - 1, x, index + 1)
            ])
            board[y][x] = tmp
            return res

        for y in range(m):
            for x in range(n):
                if dfs(y, x, 0):
                    return True

        return False
```
