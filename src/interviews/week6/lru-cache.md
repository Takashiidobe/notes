# LRU Cache

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

```java
LRUCache(int capacity) // Initialize the LRU cache with positive size capacity.
int get(int key) // Return value of the key if the key exists, otherwise return -1.
void put(int key, int value) // Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
```

The functions get and put must each run in O(1) average time complexity.

## Thought Process

### log(n) solution

A straightforward approach involves using a sorted tree to allow for CRUD operations in `log(n)` time.

You would initialize the tree with a counter starting at 0 (timestamp) and its capacity.

When you get an item, you want to update its timestamp to the newest timestamp and increment the timestamp.

If you update an item, you set it with a tuple of (timestamp, item) and then increment the timestamp.

Thus, at any given time, the first item is the one that is next to be evicted, and the last item is the last item touched.

### Improvement

A sorted map is required if we must keep the items in sorted order, and allow for operations anywhere in the map. If so, it is optimal.

In this case, we have three requirements:

1. O(1) access to any item.
2. O(1) add to end for any item, through delete + append or moving the data structure to the end.
3. O(1) pop from beginning for any item, without requiring rebalancing.

To do so, we want a data structure that remembers its insertion order, i.e. when an item has been added to the data structure. If we wrap that with a hashmap, we can get O(1) CRUD operations and O(1) move to end, which solves this problem.

One way to do this is with a python Dict or OrderedDict, since it remembers its insertion order.

```python
class LRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = dict()

    def get(self, key: int) -> int:
        if key not in cache:
            return -1
        self.cache.move_to_end(key) # we mark the item as last seen
        return self.cache[key]

    def put(self, key: int, value: int) -> None:
        self.cache[key] = value
        self.cache.move_to_end(key)
        if len(self.cache) > self.capacity:
            self.cache.popitem(last=False) # remove the first item
```
