use utils::Scanner;

pub fn algorithm(chars: Vec<char>) -> u64 {
    if chars.len() == 0 {
        return 0;
    }

    let mut curr = 1;
    let mut total = 1;
    for (left, right) in chars.iter().zip(chars.iter().skip(1)) {
        curr = if left == right { curr + 1 } else { 1 };
        total = std::cmp::max(curr, total);
    }
    total
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let sequence = scanner.split_line();

    let total = algorithm(sequence);

    println!("{:?}", total);
}

#[test]
fn test_1() {
    assert_eq!(algorithm("ATTCGGGA".chars().collect()), 3);
}
#[test]
fn test_2() {
    assert_eq!(algorithm("ATTTTCGGGA".chars().collect()), 4);
}

#[test]
fn test_3() {
    assert_eq!(algorithm("ATTCGGA".chars().collect()), 2);
}
