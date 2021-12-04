use std::collections::HashSet;
use std::iter::FromIterator;
use utils::Scanner;

pub fn algorithm(nums: Vec<u64>) -> usize {
    HashSet::<u64>::from_iter(nums.into_iter()).len()
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let _: usize = scanner.token();
    let nums = scanner.get_spaced_line_vec();

    let total = algorithm(nums);

    println!("{:?}", total);
}

#[test]
fn test_1() {
    assert_eq!(algorithm(vec![2, 3, 2, 2, 3]), 2);
}
