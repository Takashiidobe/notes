#[allow(dead_code)]
fn rotate<T>(mut vec: Vec<T>, places: usize) -> Vec<T> {
    vec.rotate_right(places);
    vec
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(rotate(vec![1, 2, 3, 4], 1), vec![4, 1, 2, 3]);
    }
    #[test]
    fn test_one() {
        assert_eq!(rotate(vec![1, 2, 3, 4], 1), vec![4, 1, 2, 3]);
    }
    #[test]
    fn test_two() {
        assert_eq!(rotate(vec![1, 2, 3, 4], 1), vec![4, 1, 2, 3]);
    }
}
