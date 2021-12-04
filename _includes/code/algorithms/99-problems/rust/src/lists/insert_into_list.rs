#[allow(dead_code)]
fn insert_at<T>(mut vec: Vec<T>, item: T, pos: usize) -> Vec<T> {
    vec.insert(pos, item);
    vec
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(insert_at(vec![], 1, 0), vec![1]);
    }

    #[test]
    fn test() {
        assert_eq!(insert_at(vec![1], 1, 0), vec![1, 1]);
    }

    #[test]
    fn test_two() {
        assert_eq!(insert_at(vec![2,], 1, 0), vec![1, 2]);
    }
}
