#[allow(dead_code)]
fn extract<T: Copy>(vec: Vec<T>, left: usize, right: usize) -> Vec<T> {
    let mut res = vec![];

    let mut i = left;

    while i < right && i < vec.len() {
        res.push(*vec.get(i).unwrap());
        i += 1;
    }

    res
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(extract::<i32>(vec![], 1, 1), vec![]);
    }

    #[test]
    fn test() {
        assert_eq!(extract(vec![1, 2, 3, 4, 5], 1, 5), vec![2, 3, 4, 5]);
    }

    #[test]
    fn test_two() {
        assert_eq!(extract(vec![1, 2, 3, 4, 5], 0, 7), vec![1, 2, 3, 4, 5]);
    }
}
