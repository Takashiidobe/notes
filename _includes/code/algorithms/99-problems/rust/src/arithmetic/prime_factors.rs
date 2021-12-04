use crate::arithmetic::list_primes::list_primes;

#[allow(dead_code)]
fn prime_factors(n: usize) -> Vec<usize> {
  if n < 2 {
    return vec![];
  }

  let factors = list_primes(n);

  factorize(n, factors, vec![])
}

#[allow(dead_code)]
fn factorize(n: usize, factor_list: Vec<usize>, mut curr_factors: Vec<usize>) -> Vec<usize> {
  if n == 0 {
    return factor_list;
  }
  for &i in &factor_list {
    if n % i == 0 {
      curr_factors.push(i);
      return factorize(n / i, factor_list, curr_factors);
    }
  }
  curr_factors
}

#[cfg(test)]
mod test {
  use super::*;

  #[test]
  fn three_fifteen() {
    assert_eq!(prime_factors(315), vec![3, 3, 5, 7]);
  }

  #[test]
  fn thirty_six() {
    assert_eq!(prime_factors(36), vec![2, 2, 3, 3]);
  }
}
