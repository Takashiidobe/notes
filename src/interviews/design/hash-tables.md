# Hash Tables

Hash tables can be designed with either a buckets approach of pointers, or with linear probing.

Linear probing involves resolving collisions by adding the item to the next open slot to the right, and deleting items by marking them as tombstones periodically.

However, the time to insert an item goes to O(n) as the load factor on a hash table goes over .5.

The way to increase performance is to artificially add tombstones into the table to boost insertion performance. This breaks up long runs which take a long time to resolve. The new tombstones that are added should occupy half of the free slots, and items should be sorted by hash. This is optimal for on disk usage.
