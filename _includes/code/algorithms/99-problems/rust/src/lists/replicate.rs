#[allow(dead_code)]
fn replicate<T: Clone>(vec: Vec<T>, times: usize) -> Vec<T> {
    let vec_len = vec.len() * times;
    let vec: Vec<T> = vec.into_iter().clone().cycle().take(vec_len).collect();
    vec
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(replicate::<i32>(vec![], 2), vec![]);
    }

    #[test]
    fn test() {
        assert_eq!(replicate(vec!['a', 'b'], 2), vec!['a', 'b', 'a', 'b']);
    }
}
