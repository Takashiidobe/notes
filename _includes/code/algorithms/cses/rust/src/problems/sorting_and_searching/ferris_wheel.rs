use utils::Scanner;

pub fn algorithm(max_weight: usize, mut children: Vec<usize>) -> u128 {
    children.sort();
    let mut gondolas = 0;
    let mut i = 0;
    let mut j = children.len() - 1;

    while i <= j {
        let right = children[j];
        let left = children[i];
        if right + left < max_weight {
            i += 1;
        }
        j -= 1;
        gondolas += 1;
    }
    gondolas
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let _: usize = scanner.token();
    let max_weight: usize = scanner.token();
    let children: Vec<usize> = scanner.get_spaced_line_vec();

    println!("{}", algorithm(max_weight, children));
}

#[test]
fn test_1() {
    assert_eq!(algorithm(10, vec![7, 2, 3, 9]), 3);
}

#[test]
fn test_2() {
    assert_eq!(algorithm(15, vec![9, 8, 8, 9, 10, 8, 5, 8, 7, 10]), 8);
}

#[test]
fn test_3() {
    assert_eq!(algorithm(20, vec![5, 9, 6, 5, 8, 9, 10, 6, 5, 6]), 5);
}
#[test]
fn test_4() {
    assert_eq!(algorithm(2, vec![1, 2, 2, 1, 1, 2, 2, 2, 2, 2]), 9);
}
