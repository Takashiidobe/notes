/*
 * @lc app=leetcode id=839 lang=rust
 *
 * [839] Similar String Groups
 *
 * https://leetcode.com/problems/similar-string-groups/description/
 *
 * algorithms
 * Hard (38.98%)
 * Total Accepted:    29.2K
 * Total Submissions: 74.8K
 * Testcase Example:  '["tars","rats","arts","star"]'
 *
 * Two strings X and Y are similar if we can swap two letters (in different
 * positions) of X, so that it equals Y. Also two strings X and Y are similar
 * if they are equal.
 * 
 * For example, "tars" and "rats" are similar (swapping at positions 0 and 2),
 * and "rats" and "arts" are similar, but "star" is not similar to "tars",
 * "rats", or "arts".
 * 
 * Together, these form two connected groups by similarity: {"tars", "rats",
 * "arts"} and {"star"}.  Notice that "tars" and "arts" are in the same group
 * even though they are not similar.  Formally, each group is such that a word
 * is in the group if and only if it is similar to at least one other word in
 * the group.
 * 
 * We are given a list strs of strings where every string in strs is an anagram
 * of every other string in strs. How many groups are there?
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: strs = ["tars","rats","arts","star"]
 * Output: 2
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: strs = ["omv","ovm"]
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= strs.length <= 100
 * 1 <= strs[i].length <= 1000
 * sum(strs[i].length) <= 2 * 10^4
 * strs[i] consists of lowercase letters only.
 * All words in strs have the same length and are anagrams of each other.
 * 
 * 
 */
impl Solution {
    pub fn num_similar_groups(strs: Vec<String>) -> i32 {
        
    }
}
