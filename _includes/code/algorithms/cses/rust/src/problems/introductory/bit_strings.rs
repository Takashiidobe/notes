use utils::Scanner;

pub fn algorithm(n: u128) -> u128 {
    let modulo = 10u128.pow(9) + 7;
    pow(2, n, modulo)
}

pub fn pow(b: u128, p: u128, md: u128) -> u128 {
    let mut ans = 1;
    for _ in 0..p {
        ans = ans * b % md;
    }
    ans
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

// #[test]
// fn test_2_bit_strings() {
//     assert_eq!(algorithm(100000000), 494499948);
// }
