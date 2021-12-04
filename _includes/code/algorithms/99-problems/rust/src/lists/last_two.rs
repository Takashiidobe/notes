#[allow(dead_code)]
fn last_two<T: Copy>(vec: Vec<T>) -> Option<Vec<T>> {
    match vec.len() {
        0 => None,
        1 => Some(vec),
        _ => Some(vec.into_iter().rev().take(2).rev().into_iter().collect()),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(last_two::<i32>(vec![]), None);
    }

    #[test]
    fn one() {
        assert_eq!(last_two::<i32>(vec![1]), Some(vec![1]));
    }

    #[test]
    fn two() {
        assert_eq!(last_two::<i32>(vec![1, 2]), Some(vec![1, 2]));
    }

    #[test]
    fn three() {
        assert_eq!(last_two::<i32>(vec![1, 2, 3]), Some(vec![2, 3]));
    }
}
