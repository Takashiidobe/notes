use utils::Scanner;

pub fn algorithm(n: u64) -> String {
    let mut copy = n.clone();
    let mut ans = vec![copy];
    while copy > 1 {
        copy = if copy % 2 == 0 {
            copy / 2
        } else {
            copy * 3 + 1
        };
        ans.push(copy);
    }
    ans.into_iter()
        .map(|d| d.to_string())
        .collect::<Vec<String>>()
        .join(" ")
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());
    let num: u64 = scanner.token();
    print!("{}", algorithm(num));
}

#[test]
fn test_1() {
    assert_eq!(algorithm(3), "3 10 5 16 8 4 2 1");
}
#[test]
fn test_2() {
    assert_eq!(algorithm(4), "4 2 1");
}

#[test]
fn test_3() {
    assert_eq!(algorithm(20), "20 10 5 16 8 4 2 1");
}
