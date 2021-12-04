use std::collections::HashMap;

use std::cmp::Eq;
use std::hash::Hash;

#[allow(dead_code)]
fn run_length_encoding<T: Hash + Eq>(vec: Vec<T>) -> Vec<(usize, T)> {
    let mut hm = HashMap::new();
    for i in vec {
        *hm.entry(i).or_insert(0) += 1;
    }

    let mut res = vec![];

    for (key, value) in hm {
        res.push((value as usize, key));
    }

    res
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(run_length_encoding::<char>(vec![]), vec![]);
    }

    #[test]
    fn test() {
        let mut input = run_length_encoding(vec!['a', 'b', 'c', 'd', 'd']);
        input.sort();
        let mut output = vec![(1, 'a'), (1, 'b'), (1, 'c'), (2, 'd')];
        output.sort();
        assert_eq!(input, output);
    }
}
