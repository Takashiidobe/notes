#[allow(dead_code)]
fn palindrome<T: PartialEq + Clone>(vec: Vec<T>) -> bool {
    let copy = vec.iter().rev();

    let iterator = copy.zip(vec.iter());

    for (first, second) in iterator {
        if let false = first == second {
            return false
        }
    }

    true
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn empty() {
        assert_eq!(palindrome::<char>(vec![]), true);
    }

    #[test]
    fn one() {
        assert_eq!(palindrome::<char>(vec!['a']), true);
    }

    #[test]
    fn palindrome() {
        assert_eq!(palindrome::<char>(vec!['a', 'b', 'a']), true);
    }

    #[test]
    fn not_palindrome() {
        assert_eq!(palindrome::<char>(vec!['a', 'b']), false);
    }
}
