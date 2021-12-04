use std::cmp::PartialEq;

#[allow(dead_code)]
fn linear_search<T: PartialEq>(arr: Vec<T>, target: T) -> Option<usize> {
    for (index, value) in arr.into_iter().enumerate() {
        if value == target {
            return Some(index);
        }
    }

    None
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_match() {
        assert_eq!(linear_search::<i32>(vec![1, 2, 3, 4], 4), Some(3));
    }

    #[test]
    fn test_none() {
        assert_eq!(linear_search::<i32>(vec![1, 2, 3, 4], 6), None);
    }

    #[test]
    fn test_empty() {
        assert_eq!(linear_search::<i32>(vec![], 4), None);
    }
}
