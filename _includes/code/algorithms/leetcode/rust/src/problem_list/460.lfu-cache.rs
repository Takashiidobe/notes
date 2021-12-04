/*
 * @lc app=leetcode id=460 lang=rust
 *
 * [460] LFU Cache
 *
 * https://leetcode.com/problems/lfu-cache/description/
 *
 * algorithms
 * Hard (34.87%)
 * Total Accepted:    86.7K
 * Total Submissions: 246.7K
 * Testcase Example:  '["LFUCache","put","put","get","put","get","get","put","get","get","get"]\n' +
  '[[2],[1,1],[2,2],[1],[3,3],[2],[3],[4,4],[1],[3],[4]]'
 *
 * Design and implement a data structure for Least Frequently Used (LFU)
 * cache.
 * 
 * Implement the LFUCache class:
 * 
 * 
 * LFUCache(int capacity) Initializes the object with the capacity of the data
 * structure.
 * int get(int key) Gets the value of the key if the key exists in the cache.
 * Otherwise, returns -1.
 * void put(int key, int value) Sets or inserts the value if the key is not
 * already present. When the cache reaches its capacity, it should invalidate
 * the least frequently used item before inserting a new item. For this
 * problem, when there is a tie (i.e., two or more keys with the same
 * frequency), the least recently used key would be evicted.
 * 
 * 
 * Notice that the number of times an item is used is the number of calls to
 * the get and put functions for that item since it was inserted. This number
 * is set to zero when the item is removed.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input
 * ["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get",
 * "get"]
 * [[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
 * Output
 * [null, null, null, 1, null, -1, 3, null, -1, 3, 4]
 * 
 * Explanation
 * LFUCache lfu = new LFUCache(2);
 * lfu.put(1, 1);
 * lfu.put(2, 2);
 * lfu.get(1);      // return 1
 * lfu.put(3, 3);   // evicts key 2
 * lfu.get(2);      // return -1 (not found)
 * lfu.get(3);      // return 3
 * lfu.put(4, 4);   // evicts key 1.
 * lfu.get(1);      // return -1 (not found)
 * lfu.get(3);      // return 3
 * lfu.get(4);      // return 4
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= capacity, key, value <= 10^4
 * At most 10^5 calls will be made to get and put.
 * 
 * 
 * 
 * Follow up: Could you do both operations in O(1) time complexity? 
 */
struct LFUCache {

}


/** 
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl LFUCache {

    fn new(capacity: i32) -> Self {
        
    }
    
    fn get(&self, key: i32) -> i32 {
        
    }
    
    fn put(&self, key: i32, value: i32) {
        
    }
}

/**
 * Your LFUCache object will be instantiated and called as such:
 * let obj = LFUCache::new(capacity);
 * let ret_1: i32 = obj.get(key);
 * obj.put(key, value);
 */
