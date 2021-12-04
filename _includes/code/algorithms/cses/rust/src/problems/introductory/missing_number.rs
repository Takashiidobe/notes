use utils::Scanner;

pub fn algorithm(n: u64, nums: Vec<u64>) -> u64 {
    let total = n * (n + 1) / 2;
    let num_total: u64 = nums.into_iter().sum();
    total - num_total
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let n: u64 = scanner.token();
    let nums: Vec<u64> = scanner.get_spaced_line_vec();

    println!("{}", algorithm(n, nums));
}

#[test]
fn test_1() {
    assert_eq!(algorithm(5, vec![2, 3, 1, 5]), 4);
}
#[test]
fn test_2() {
    assert_eq!(algorithm(3, vec![1, 2]), 3);
}

#[test]
fn test_3() {
    assert_eq!(algorithm(6, vec![1, 5, 4, 3, 2]), 6);
}
