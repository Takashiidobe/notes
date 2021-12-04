#[allow(dead_code)]
fn last<T>(vec: Vec<T>) -> Option<T> {
    vec.into_iter().last()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_match() {
        assert_eq!(last::<i32>(vec![1, 2, 3, 4]), Some(4));
    }

    #[test]
    fn test_empty() {
        assert_eq!(last::<i32>(vec![]), None);
    }
}
