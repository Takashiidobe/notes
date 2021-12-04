#[allow(dead_code)]
fn flatten<T>(vec: Vec<Vec<T>>) -> Vec<T> {
    vec.into_iter().flatten().collect::<Vec<T>>()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(flatten::<i32>(vec![vec![]]), vec![])
    }

    #[test]
    fn one_level() {
        assert_eq!(flatten::<i32>(vec![vec![1]]), vec![1])
    }

    #[test]
    fn two_items_in_one_level() {
        assert_eq!(
            flatten::<i32>(vec![vec![1, 2], vec![3, 4]]),
            vec![1, 2, 3, 4]
        )
    }
}
