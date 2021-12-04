/*
 * @lc app=leetcode id=1436 lang=rust
 *
 * [1436] Destination City
 *
 * https://leetcode.com/problems/destination-city/description/
 *
 * algorithms
 * Easy (77.17%)
 * Total Accepted:    50.7K
 * Total Submissions: 65.6K
 * Testcase Example:  '[["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]'
 *
 * You are given the array paths, where paths[i] = [cityAi, cityBi] means there
 * exists a direct path going from cityAi to cityBi. Return the destination
 * city, that is, the city without any path outgoing to another city.
 *
 * It is guaranteed that the graph of paths forms a line without any loop,
 * therefore, there will be exactly one destination city.
 *
 *
 * Example 1:
 *
 *
 * Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao
 * Paulo"]]
 * Output: "Sao Paulo"
 * Explanation: Starting at "London" city you will reach "Sao Paulo" city which
 * is the destination city. Your trip consist of: "London" -> "New York" ->
 * "Lima" -> "Sao Paulo".
 *
 *
 * Example 2:
 *
 *
 * Input: paths = [["B","C"],["D","B"],["C","A"]]
 * Output: "A"
 * Explanation: All possible trips are:
 * "D" -> "B" -> "C" -> "A".
 * "B" -> "C" -> "A".
 * "C" -> "A".
 * "A".
 * Clearly the destination city is "A".
 *
 *
 * Example 3:
 *
 *
 * Input: paths = [["A","Z"]]
 * Output: "Z"
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= paths.length <= 100
 * paths[i].length == 2
 * 1 <= cityAi.length, cityBi.length <= 10
 * cityAi != cityBi
 * All strings consist of lowercase and uppercase English letters and the space
 * character.
 *
 *
 */

use std::collections::HashSet;

#[allow(dead_code)]
struct Solution {}

#[allow(dead_code)]
impl Solution {
    pub fn dest_city(paths: Vec<Vec<String>>) -> String {
        let mut left = HashSet::new();
        let mut right = HashSet::new();
        for path in paths {
            left.insert(path[0].clone());
            right.insert(path[1].clone());
        }
        let mut ans = "".to_string();
        for city in right {
            if !left.contains(&city) {
                ans = city.to_string();
            }
        }
        ans
    }
}

#[test]
fn example() {
    assert_eq!(
        Solution::dest_city(vec![
            leetcode_prelude::vec_string!["London", "New York"],
            leetcode_prelude::vec_string!["New York", "Lima"],
            leetcode_prelude::vec_string!["Lima", "Sao Paulo"]
        ]),
        "Sao Paulo"
    );
}
