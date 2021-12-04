#[allow(dead_code)]
fn duplicate<T: Clone>(vec: Vec<T>) -> Vec<T> {
    let vec_len = vec.len() * 2;
    let res: Vec<T> = vec
        .into_iter()
        .cycle()
        .take(vec_len)
        .to_owned()
        .collect::<Vec<T>>();

    res
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(duplicate::<i32>(vec![]), vec![]);
    }

    #[test]
    fn test() {
        assert_eq!(duplicate(vec![1, 2, 3]), vec![1, 2, 3, 1, 2, 3]);
    }
}
