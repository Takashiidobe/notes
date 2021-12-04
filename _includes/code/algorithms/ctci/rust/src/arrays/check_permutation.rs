use std::collections::HashMap;
#[allow(dead_code)]
fn check_permutation(a: &str, b: &str) -> bool {
    let mut first_map = HashMap::new();
    let mut second_map = HashMap::new();

    for c in a.chars() {
        *first_map.entry(c).or_insert(0) += 1;
    }

    for c in b.chars() {
        *second_map.entry(c).or_insert(0) += 1;
    }

    if first_map == second_map {
        return true;
    }

    false
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(check_permutation("", ""), true);
    }

    #[test]
    fn test() {
        assert_eq!(check_permutation("olleh", "hlleo"), true);
    }

    #[test]
    fn test_false() {
        assert_eq!(check_permutation("apple", "hlleo"), false);
    }
}
