# Flood Fill

An image is represented by an m x n integer grid image where `image[i][j]` represents the pixel value of the image.

You are also given three integers sr, sc, and color. You should perform a flood fill on the image starting from the pixel image[sr][sc].

To perform a flood fill, consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color), and so on. Replace the color of all of the aforementioned pixels with color.

Return the modified image after performing the flood fill.

Example 1:

```
Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation: From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected to the starting pixel.
```

Example 2:

```
Input: image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, color = 0
Output: [[0,0,0],[0,0,0]]
Explanation: The starting pixel is already colored 0, so no changes are made to the image.
```

## Solution

First, we create a deque with the starting pixel. (sr, sc).

Then we take that coordinate, and if it matches the starting color, we
add all its neighbors to the queue, painting it to the new color if it
matches the color we want to flood fill.

```python
class Solution:
    def floodFill(self, image: List[List[int]], sr: int, sc: int, color: int) -> List[List[int]]:
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

        def inbounds(y, x):
            return 0 <= y < len(image) and 0 <= x < len(image[0])

        q = deque([(sr, sc)])

        while q:
            y, x = q.popleft()
            tile_color = image[y][x]
            if tile_color != color:
                image[y][x] = color
                for dy, dx in directions:
                    new_y, new_x = dy + y, dx + x
                    if inbounds(new_y, new_x) and image[new_y][new_x] == tile_color:
                        q.append((new_y, new_x))

        return image
```
