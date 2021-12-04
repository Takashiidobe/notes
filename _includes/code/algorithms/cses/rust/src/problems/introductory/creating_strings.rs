use std::collections::HashSet;
use utils::Scanner;

pub fn algorithm(s: String) -> (u64, Vec<String>) {
    fn traverse(mut curr: String, mut remaining: Vec<char>) -> String {
        if remaining.len() < 1 {
            return curr;
        }

        for c in remaining.into_iter() {
            let mut cloned_str = curr.clone();
            cloned_str += c.to_str();
            let mut cleaned_vec = remaining.clone();
            cleaned_vec.remove(c.to_str()).unwrap();
            return traverse(cloned_str, cleaned_vec);
        }
    }
    (20, vec![])
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let s: String = scanner.get_line();

    let total = algorithm(s);

    println!("{:?}", total);
}

#[test]
fn test_1() {
    assert_eq!(
        algorithm("aabac"),
        (
            20,
            vec![
                "aaabc", "aaacb", "aabac", "aabca", "aacab", "aacba", "abaac", "abaca", "abcaa",
                "acaab", "acaba", "acbaa", "baaac", "baaca", "bacaa", "bcaaa", "caaab", "caaba",
                "cabaa", "cbaaa"
            ]
        )
    );
}
