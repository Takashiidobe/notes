# LFU Cache

Design and implement a data structure for a Least Frequently Used (LFU) cache.

Implement the LFUCache class:

```java
LFUCache(int capacity) // Initializes the object with the capacity of the data structure.
int get(int key) // Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
void put(int key, int value) // Update the value of the key if present, or inserts the key if not already present. When the cache reaches its capacity, it should invalidate and remove the least frequently used key before inserting a new item. For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be invalidated.
```

To determine the least frequently used key, a use counter is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.

When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). The use counter for a key in the cache is incremented either a get or put operation is called on it.

The functions get and put must each run in O(1) average time complexity.

## Thought Process

A less optimal approach could be done with a sorted tree. Imagine a tree of `key -> (access_count, timestamp, value)`, where timestamps are always incremented per operation.

When we get an item, we can fetch its contents, and increment its access count and set its timestamp to the current value, and return the value to the caller.

When we put an item, we can update its access_count, update its timestamp, and value. If we append, we can append the item and check to see what should be evicted.

## Solution

To handle this, we need two dictionaries: one dictionary of keys -> [value, count], and another dictionary of OrderedDicts, that will create buckets of cache counts in insertion order, so we can evict them when necessary, and a counter to the leftmost filled bucket (so we can evict items from there).

When we get an item, we increment its access count in the dictionary, and then we remove the key from the dictionary of ordered dicts, and move it to its next bucket. If we find that there are no more items in our bucket (since we moved an item from one bucket to its next item), we increment our leftmost pointer, which points to the first bucket of items to evict.

When we put an item, we update its count, move it to the right bucket, then change its value. If we must evict, we take the leftmost pointer, and evict the first item from that bucket. Otherwise, we just append the item, and reset our leftmost pointer to 1.

```python
from collections import OrderedDict, defaultdict

class LFUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = dict() # key -> [value, count]
        self.cache_counts = defaultdict(OrderedDict) # count -> OrderedDict(key -> None)
        self.min_count = 0

    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1

        value, old_count = self.cache[key] # grab the value and access count from cache
        self.cache[key][1] += 1 # we increment the access count
        self.cache_counts[old_count].pop(key) # remove previous entry
        self.update_cache_counts(key, old_count + 1) # update entry

        if old_count == self.min_count and len(self.cache_counts[old_count]) == 0:
            self.min_count = old_count + 1 # update the leftmost pointer to evict

        return value

    def put(self, key: int, value: int) -> None:
        if self.capacity <= 0:
            return

        if key in self.cache:
            _ = self.get(key) # update count
            self.cache[key][0] = value # update the value
            return

        if len(self.cache) == self.capacity: # if we must evict
            rm_key, _ = self.cache_counts[self.min_count].popitem(last=False) # grab the first item to evict
            self.cache.pop(rm_key) # evict it

        self.cache[key] = [value, 1] # otherwise, append
        self.update_cache_counts(key, 1) # update lookup map
        self.min_count = 1 # set

    def update_cache_counts(self, key: int, count: int):
        self.cache_counts[count][key] = None
```
