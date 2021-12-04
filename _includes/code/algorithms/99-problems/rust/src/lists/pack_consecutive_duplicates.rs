#[allow(dead_code)]
fn pack_consecutive_duplicates<T: PartialEq + Copy>(vec: Vec<T>) -> Vec<Vec<T>> {
    if vec.len() == 0 {
        return vec![vec![]];
    }

    if vec.len() == 1 {
        return vec![vec![*vec.get(0).unwrap()]];
    }

    let mut i = 0;
    let mut res = vec![];
    let mut curr = *vec.get(0).unwrap();

    while i < vec.len() {
        let mut group = vec![curr];
        let element = *vec.get(i).unwrap();
        while curr == element {
            group.push(element);
            i += 1;
            break;
        }
        res.push(group);
        curr = element;
        i += 1;
    }

    res
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(
            pack_consecutive_duplicates::<char>(vec!['a']),
            vec![vec!['a']]
        );
    }

    #[test]
    fn test() {
        assert_eq!(
            pack_consecutive_duplicates::<char>(vec!['a', 'a']),
            vec![vec!['a', 'a']]
        );
    }

    #[test]
    fn test_two() {
        let mut vec = vec![vec!['a', 'a'], vec!['b', 'b'], vec!['a']];
        vec.sort();

        let mut sorted_question =
            pack_consecutive_duplicates::<char>(vec!['a', 'a', 'b', 'b', 'a']);

        sorted_question.sort();
        assert_eq!(sorted_question, vec);
    }
}
