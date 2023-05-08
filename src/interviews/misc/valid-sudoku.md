Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

1. Each row must contain the digits 1-9 without repetition.
2. Each column must contain the digits 1-9 without repetition.
3. Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.

Note:

1. A Sudoku board (partially filled) could be valid but is not necessarily solvable.
2. Only the filled cells need to be validated according to the mentioned rules.

```python
class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        rows = [set() for _ in range(9)]
        cols = [set() for _ in range(9)]
        squares = [[set() for _ in range(3)] for _ in range(3)]

        for row in range(9):
            for col in range(9):
                num = board[row][col]
                if num == ".":
                    continue
                if num in rows[row] or num in cols[col] or num in squares[row // 3][col // 3]:
                    return False
                rows[row].add(num)
                cols[col].add(num)
                squares[row // 3][col // 3].add(num)

        return True
```
