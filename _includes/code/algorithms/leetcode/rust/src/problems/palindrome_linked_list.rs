/*
 * @lc app=leetcode id=234 lang=rust
 *
 * [234] Palindrome Linked List
 *
 * https://leetcode.com/problems/palindrome-linked-list/description/
 *
 * algorithms
 * Easy (39.75%)
 * Total Accepted:    505.2K
 * Total Submissions: 1.3M
 * Testcase Example:  '[1,2]'
 *
 * Given a singly linked list, determine if it is a palindrome.
 *
 * Example 1:
 *
 *
 * Input: 1->2
 * Output: false
 *
 * Example 2:
 *
 *
 * Input: 1->2->2->1
 * Output: true
 *
 * Follow up:
 * Could you do it in O(n) time and O(1) space?
 *
 */
use leetcode_prelude::*;

#[allow(dead_code)]
struct Solution {}

#[allow(dead_code)]
impl Solution {
    fn to_list(head: &Option<Box<ListNode>>) -> Vec<i32> {
        let mut head = head;
        let mut v = vec![];
        while head.is_some() {
            v.push(head.as_ref().unwrap().val);
            head = &head.as_ref().unwrap().next;
        }
        v
    }
    pub fn is_palindrome(head: &Option<Box<ListNode>>) -> bool {
        let v = Solution::to_list(head);
        let mut i = 0;
        let mut j = v.len() - 1;

        while i < j {
            if v[i] != v[j] {
                return false;
            }
            i += 1;
            j -= 1;
        }
        true
    }
}

#[test]
fn valid() {
    let list = linkedlist![1, 2, 2, 1];
    assert_eq!(Solution::is_palindrome(&list), true);
}

#[test]
fn invalid() {
    let list = linkedlist![1, 2, 3, 1];
    assert_eq!(Solution::is_palindrome(&list), false);
}
