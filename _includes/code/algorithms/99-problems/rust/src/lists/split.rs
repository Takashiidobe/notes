#[allow(dead_code)]
fn split<T: Clone>(vec: Vec<T>, length: usize) -> Vec<Vec<T>> {
    if length > vec.len() {
        return vec![vec, vec![]];
    }

    let mut res = vec![];

    for chunk in vec.chunks(length) {
        res.push(chunk.clone().to_vec());
    }

    res
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(split::<i32>(vec![], 2), vec![vec![], vec![]]);
    }

    #[test]
    fn test() {
        assert_eq!(
            split::<i32>(vec![1, 2, 3, 4], 2),
            vec![vec![1, 2], vec![3, 4]]
        );
    }

    #[test]
    fn test_two() {
        assert_eq!(split(vec![1, 2, 3, 4], 5), vec![vec![1, 2, 3, 4], vec![]]);
    }
}
