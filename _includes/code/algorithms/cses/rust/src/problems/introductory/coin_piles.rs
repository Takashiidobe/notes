use utils::Scanner;

pub fn algorithm(left: u64, right: u64) -> bool {
    if (left + right) % 3 != 0 {
        return false;
    }
    if left * 2 < right || right * 2 < left {
        return false;
    }

    true
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let n: usize = scanner.token();

    let mut coords: Vec<(u64, u64)> = vec![];
    for _ in 0..n {
        coords.push(scanner.get_line_to_tuple())
    }

    for i in 0..n {
        if algorithm(coords[i].0, coords[i].1) {
            println!("YES");
        } else {
            println!("NO");
        }
    }
}

#[test]
fn test_1() {
    assert_eq!(algorithm(2, 1), true);
}
#[test]
fn test_2() {
    assert_eq!(algorithm(2, 2), false);
}

#[test]
fn test_3() {
    assert_eq!(algorithm(3, 3), true);
}
#[test]
fn test_4() {
    assert_eq!(algorithm(4, 4), false);
}
