---
title: 78-zero-matrix
---

Matrix\"

## Problem

Given a two-dimensional matrix of integers, for each zero in the
original matrix, replace all values in its row and column with zero, and
return the resulting matrix.

## Explanation

We want to first iterate through the matrix and count the rows and cols
that have a 0, to zero fill later. We\'ll use two sets for this, rows
and cols. Then, we\'ll iterate again, and if our row number is in rows
or our col number is in cols, we\'ll set the current cell to 0. Easy.

## Solution

```py
class Solution:
    def solve(self, matrix):
        row_len = len(matrix)
        col_len = len(matrix[0])
        rows = set()
        cols = set()

        for i in range(row_len):
            for j in range(col_len):
                if matrix[i][j] == 0:
                    rows.add(i)
                    cols.add(j)

        for i in range(row_len):
            for j in range(col_len):
                if i in rows or j in cols:
                    matrix[i][j] = 0

        return matrix
```
