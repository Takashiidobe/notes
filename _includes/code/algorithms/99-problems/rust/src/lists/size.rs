#[allow(dead_code)]
fn size<T>(vec: Vec<T>) -> usize {
    vec.len()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(size::<i32>(vec![]), 0);
    }

    #[test]
    fn one() {
        assert_eq!(size::<i32>(vec![1]), 1);
    }

    #[test]
    fn two() {
        assert_eq!(size::<i32>(vec![1, 2]), 2);
    }
}
