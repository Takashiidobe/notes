#[allow(dead_code)]
fn drop_nth<T>(vec: Vec<T>, n: usize) -> Vec<T> {
    let copy = vec
        .into_iter()
        .enumerate()
        .filter(|&(i, _)| (i + 1) % n != 0)
        .map(|(_, v)| v)
        .collect();

    copy
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(drop_nth::<i32>(vec![], 1), vec![]);
    }

    #[test]
    fn test() {
        assert_eq!(drop_nth((1..10).collect(), 3), vec![1, 2, 4, 5, 7, 8]);
    }

    #[test]
    fn test_two() {
        assert_eq!(drop_nth((1..10).collect(), 2), vec![1, 3, 5, 7, 9]);
    }
}
