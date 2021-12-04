class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        matrix = []
        for i in range(m):
            matrix.append([])
            for j in range(n):
                matrix[i].append(0)

        for i in range(m):
            for j in range(n):
                if i == 0 or j == 0:
                    matrix[i][j] = 1

        for i in range(m):
            for j in range(n):
                if i > 0 and j > 0:
                    matrix[i][j] = matrix[i-1][j] + matrix[i][j-1]

        return matrix[m-1][n-1]
