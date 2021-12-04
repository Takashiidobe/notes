#[allow(dead_code)]
pub fn is_prime(n: usize) -> bool {
    if n < 2 {
        return false;
    }

    (2..n).all(|a| n % a != 0)
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn two_is_prime() {
        assert_eq!(is_prime(2), true);
    }

    #[test]
    fn not_prime() {
        assert_eq!(is_prime(51), false);
    }

    #[test]
    fn prime() {
        assert_eq!(is_prime(83), true);
    }
}
