---
title: "Sorting"
---

# Sorting

Prev: [data-structures](data-structures.md)
Next: [divide-and-conquer](divide-and-conquer.md)

1. The Grinch is given the job of partitioning $2n$ players into two teams of $n$
players each. Each player has a numerical rating that measures how good he or
she is at the game. The Grinch seeks to divide the players as unfairly as possible,
so as to create the biggest possible talent imbalance between the teams. Show
how the Grinch can do the job in $O(n log n)$ time.

This can be done by sorting the array of ratings and then splitting the team into [..mid] and [mid+1..]:

```python
def unbalanced_teams(ratings: List[int]) -> (List[int], List[int]):
    sorted_ratings = sorted(ratings)
    mid = len(sorted_ratings) // 2
    return (sorted_ratings[0..mid], sorted_ratings[mid+1..])
```

Prev: [data-structures](data-structures.md)
Next: [divide-and-conquer](divide-and-conquer.md)
