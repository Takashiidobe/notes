#[allow(dead_code)]
fn range(left: i32, right: i32) -> Vec<i32> {
    let res = (left..=right).collect();
    res
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(range(0, 0), vec![0]);
    }

    #[test]
    fn test_one() {
        assert_eq!(range(0, 5), (0..=5).collect::<Vec<i32>>());
    }

    #[test]
    fn test_two() {
        assert_eq!(range(0, 10), (0..=10).collect::<Vec<i32>>());
    }
}
