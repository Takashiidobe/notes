#[allow(dead_code)]
fn kth_element<'a, T>(vec: Vec<T>, pos: usize) -> Option<T> {
    vec.into_iter().nth(pos)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(kth_element::<i32>(vec![], 0), None);
    }

    #[test]
    fn out_of_bounds() {
        assert_eq!(kth_element::<i32>(vec![1, 2, 3], 5), None);
    }

    #[test]
    fn correct() {
        assert_eq!(kth_element::<i32>(vec![1, 2, 3], 1), Some(2));
    }
}
