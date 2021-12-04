use crate::arithmetic::gcd::gcd;

#[allow(dead_code)]
fn coprime(left: i32, right: i32) -> bool {
    return match gcd(left, right) {
        1 => true,
        _ => false,
    };
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn coprime_test() {
        assert_eq!(coprime(13, 27), true);
    }
    #[test]
    fn not_coprime() {
        assert_eq!(coprime(20536, 7826), false);
    }
    #[test]
    fn not_prime() {
        assert_eq!(coprime(2, 2), false);
    }
}
