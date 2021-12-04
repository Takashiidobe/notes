use utils::Scanner;

pub fn algorithm(n: usize) -> Option<Vec<usize>> {
    if n == 2 || n == 3 {
        return None;
    }

    let mut v = vec![];

    for i in (2..=n).step_by(2) {
        v.push(i);
    }

    for i in (1..=n).step_by(2) {
        v.push(i);
    }

    Some(v)
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let n: usize = scanner.token();

    match algorithm(n) {
        Some(v) => {
            for i in v.iter() {
                if *i != v.len() - 1 {
                    print!("{} ", &i);
                } else {
                    println!("{}", &i);
                }
            }
        }
        None => println!("NO SOLUTION"),
    }
}

#[test]
fn test_1() {
    assert_eq!(algorithm(5), Some(vec![2, 4, 1, 3, 5]));
}
#[test]
fn test_2() {
    assert_eq!(algorithm(3), None);
}

#[test]
fn test_3() {
    assert_eq!(algorithm(8), Some(vec![2, 4, 6, 8, 1, 3, 5, 7]));
}
#[test]
fn test_4() {
    assert_eq!(algorithm(4), Some(vec![2, 4, 1, 3]));
}
