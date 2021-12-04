#[allow(dead_code)]
fn reverse<T>(vec: Vec<T>) -> Vec<T> {
    vec.into_iter().rev().collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(reverse::<i32>(vec![]), vec![]);
    }

    #[test]
    fn one() {
        assert_eq!(reverse::<i32>(vec![1]), vec![1]);
    }

    #[test]
    fn two() {
        assert_eq!(reverse::<i32>(vec![1, 2]), vec![2, 1]);
    }
}
