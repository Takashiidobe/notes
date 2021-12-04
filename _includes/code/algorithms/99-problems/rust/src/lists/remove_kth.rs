#[allow(dead_code)]
fn remove_kth<T>(vec: Vec<T>, k: usize) -> Vec<T> {
    let res = vec
        .into_iter()
        .enumerate()
        .filter(|&(i, _)| i != k)
        .map(|(_, e)| e)
        .collect();

    res
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(remove_kth::<i32>(vec![], 1), vec![]);
    }

    #[test]
    fn test_one() {
        assert_eq!(remove_kth(vec![1, 2, 3, 4], 1), vec![1, 3, 4]);
    }

    #[test]
    fn test_two() {
        assert_eq!(remove_kth(vec![1, 2, 3, 4], 2), vec![1, 2, 4]);
    }
}
