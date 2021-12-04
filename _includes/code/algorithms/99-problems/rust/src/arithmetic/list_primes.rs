use crate::arithmetic::prime::is_prime;

#[allow(dead_code)]
pub fn list_primes(n: usize) -> Vec<usize> {
  let mut factors = vec![];

  for i in 2..n {
    if is_prime(i) {
      factors.push(i);
    }
  }

  factors
}

#[cfg(test)]
mod test {
  use super::*;

  #[test]
  fn three_fifteen() {
    assert_eq!(list_primes(13), vec![2, 3, 5, 7, 11]);
  }

  #[test]
  fn thirty_six() {
    assert_eq!(
      list_primes(36),
      vec![2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31]
    );
  }
}
