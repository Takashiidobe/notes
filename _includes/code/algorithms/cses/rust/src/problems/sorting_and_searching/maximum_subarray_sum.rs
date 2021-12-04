use utils::Scanner;

pub fn algorithm(array: Vec<i32>) -> i32 {
    let mut curr = array[0];
    let mut max_so_far = array[0];
    for i in array {
        curr = std::cmp::max(0, curr + i);
        max_so_far = std::cmp::max(curr, max_so_far);
    }

    max_so_far
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let _: usize = scanner.token();

    let array: Vec<i32> = scanner.get_spaced_line_vec();

    println!("{}", algorithm(array));
}

#[test]
fn test_1() {
    assert_eq!(algorithm(vec![-1, 3, -2, 5, 3, -5, 2, 2]), 9);
}
