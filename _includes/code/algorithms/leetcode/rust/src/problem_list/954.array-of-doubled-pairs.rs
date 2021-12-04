/*
 * @lc app=leetcode id=954 lang=rust
 *
 * [954] Array of Doubled Pairs
 *
 * https://leetcode.com/problems/array-of-doubled-pairs/description/
 *
 * algorithms
 * Medium (35.56%)
 * Total Accepted:    21.2K
 * Total Submissions: 60.1K
 * Testcase Example:  '[3,1,3,6]'
 *
 * Given an array of integers A with even length, return true if and only if it
 * is possible to reorder it such that A[2 * i + 1] = 2 * A[2 * i] for every 0
 * <= i < len(A) / 2.
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: A = [3,1,3,6]
 * Output: false
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: A = [2,1,2,6]
 * Output: false
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: A = [4,-2,2,-4]
 * Output: true
 * Explanation: We can take two groups, [-2,-4] and [2,4] to form [-2,-4,2,4]
 * or [2,4,-2,-4].
 * 
 * 
 * Example 4:
 * 
 * 
 * Input: A = [1,2,4,16,8,4]
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= A.length <= 3 * 10^4
 * A.length is even.
 * -10^5 <= A[i] <= 10^5
 * 
 * 
 */
impl Solution {
    pub fn can_reorder_doubled(a: Vec<i32>) -> bool {
        
    }
}
