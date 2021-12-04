#[allow(dead_code)]
fn eliminate_consecutive_dupes<T: PartialEq>(mut vec: Vec<T>) -> Vec<T> {
    vec.dedup();
    vec
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(eliminate_consecutive_dupes::<i32>(vec![]), vec![]);
    }

    #[test]
    fn one_element() {
        assert_eq!(eliminate_consecutive_dupes::<i32>(vec![1]), vec![1]);
    }

    #[test]
    fn filled() {
        assert_eq!(
            eliminate_consecutive_dupes::<&str>(vec![
                "a", "a", "a", "a", "b", "c", "c", "a", "a", "d", "e", "e", "e", "e"
            ]),
            vec!["a", "b", "c", "a", "d", "e"]
        );
    }
}
