use std::collections::HashSet;

#[allow(dead_code)]
fn is_unique(s: &str) -> bool {
    let mut m = HashSet::new();
    for c in s.chars() {
        if m.contains(&c) {
            return false;
        } else {
            m.insert(c);
        }
    }

    true
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test() {
        assert_eq!(is_unique("alo"), true);
    }

    #[test]
    fn test_1() {
        assert_eq!(is_unique("hello"), false);
    }
}
