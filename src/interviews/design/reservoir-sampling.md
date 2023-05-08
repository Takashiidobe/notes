# Reservoir Sampling

Given a stream of data, select k items at random.

(The story was making grep work by returning random samples instead of
the whole data set (that was too heavy to store in memory)).

## Halfway Solutions

1. Pick an item with probability k/n
2. Store all items, then pick k of them
3. Pick the first k items

```python
import random

input_array = [1, 7, 4, 8, 2, 6, 5, 9]

k = 4
n = len(input_array)

output = []
for i in range(k):
  output.append(input_array[i])
for j in range(k,n):
  index = random.randint(0, j)
  if index < k:
    output[index] = input_array[j]

print(f"Input array: {input_array}")
print(f"Output array: {output}")
```
