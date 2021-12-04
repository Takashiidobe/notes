/*
 * @lc app=leetcode id=447 lang=rust
 *
 * [447] Number of Boomerangs
 *
 * https://leetcode.com/problems/number-of-boomerangs/description/
 *
 * algorithms
 * Easy (52.08%)
 * Total Accepted:    70.9K
 * Total Submissions: 135.9K
 * Testcase Example:  '[[0,0],[1,0],[2,0]]'
 *
 * You are given n points in the plane that are all distinct, where points[i] =
 * [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance
 * between i and j equals the distance between i and k (the order of the tuple
 * matters).
 * 
 * Return the number of boomerangs.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: points = [[0,0],[1,0],[2,0]]
 * Output: 2
 * Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and
 * [[1,0],[2,0],[0,0]].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: points = [[1,1],[2,2],[3,3]]
 * Output: 2
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: points = [[1,1]]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == points.length
 * 1 <= n <= 500
 * points[i].length == 2
 * -10^4 <= xi, yi <= 10^4
 * All the points are unique.
 * 
 * 
 */
impl Solution {
    pub fn number_of_boomerangs(points: Vec<Vec<i32>>) -> i32 {
        
    }
}
