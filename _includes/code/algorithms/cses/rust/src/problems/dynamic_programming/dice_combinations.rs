use utils::Scanner;

pub fn algorithm(_: u128) -> u128 {
    0
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let n: u128 = scanner.token();

    let total = algorithm(n);

    println!("{:?}", total);
}

#[test]
fn test_1() {
    assert_eq!(algorithm(3), 8);
}

#[test]
fn test_2() {
    assert_eq!(algorithm(100000000), 494499948);
}
