# Make an LRU cache use less memory

A traditional LRU cache (with a hashmap and a doubly linked list) is both slow and memory intensive.

We can approximate a good LRU algorithm by augmenting our data structure with a "use" bit. Each item has a use bit that starts off at 0 (not recently used) and is set to 1 when reaccessed, and the operating system can periodically set pages to 0 after a certain amount of time (showing the page hasn't been used recently). The hand checks each page and sees if it is set to 0 (unused). If so, it will evict that page. If not, it sets that page to 0 and continues on. Thus, if all the pages have been recently used, it will scan and then evict the page it started at.

This is inprecise, and can have O(n) runtime to evict an item, but costs you a bit of memory per page, which is much less than a hashmap and doubly linked list would cost you.

If you must manage the marking of items as well, one way is to allocate a circular deque that would contain memory accesses.
Every time you read/write to an index, you would add that item to the queue, and increment the "in-use" bit of the item.
When you circle around to a location that is in use, you would decrement its "in-use" bit, before reusing the memory slot.
That allows you to approximate LRU much better, but with bounded memory usage (this is configurable based on how much accuracy is desired).

If you reduce this to 1 bit, you would get some unfair results (a hot item might be evicted), but there is little overhead.
If you use 8 bits, error is bounded by the size of the queue to the log n of the bits, which is a fair tradeoff (you can make a smaller queue and use fewer bits).
