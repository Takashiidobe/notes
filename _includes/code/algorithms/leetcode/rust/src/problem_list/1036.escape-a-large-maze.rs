/*
 * @lc app=leetcode id=1036 lang=rust
 *
 * [1036] Escape a Large Maze
 *
 * https://leetcode.com/problems/escape-a-large-maze/description/
 *
 * algorithms
 * Hard (35.18%)
 * Total Accepted:    10.8K
 * Total Submissions: 30.8K
 * Testcase Example:  '[[0,1],[1,0]]\n[0,0]\n[0,2]'
 *
 * In a 1 million by 1 million grid, the coordinates of each grid square are
 * (x, y).
 * 
 * We start at the source square and want to reach the target square.  Each
 * move, we can walk to a 4-directionally adjacent square in the grid that
 * isn't in the given list of blocked squares.
 * 
 * Return true if and only if it is possible to reach the target square through
 * a sequence of moves.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
 * Output: false
 * Explanation: The target square is inaccessible starting from the source
 * square, because we can't walk outside the grid.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: blocked = [], source = [0,0], target = [999999,999999]
 * Output: true
 * Explanation: Because there are no blocked cells, it's possible to reach the
 * target square.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= blocked.length <= 200
 * blocked[i].length == 2
 * 0 <= blocked[i][j] < 10^6
 * source.length == target.length == 2
 * 0 <= source[i][j], target[i][j] < 10^6
 * source != target
 * 
 * 
 */
impl Solution {
    pub fn is_escape_possible(blocked: Vec<Vec<i32>>, source: Vec<i32>, target: Vec<i32>) -> bool {
        
    }
}
