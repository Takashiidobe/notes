#[allow(dead_code)]
pub fn gcd(left: i32, right: i32) -> i32 {
    if left == right {
        return left;
    }

    if left < right {
        let left_factors: Vec<i32> = (1..=left).into_iter().filter(|a| left % a == 0).collect();
        for factor in left_factors.into_iter().rev() {
            if right % factor == 0 {
                return factor;
            }
        }
    }

    if left > right {
        let right_factors: Vec<i32> = (1..=right).into_iter().filter(|a| right % a == 0).collect();

        for factor in right_factors.into_iter().rev() {
            if left % factor == 0 {
                return factor;
            }
        }
    }

    1
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test_1() {
        assert_eq!(gcd(13, 27), 1);
    }
    #[test]
    fn test_2() {
        assert_eq!(gcd(9, 27), 9);
    }
    #[test]
    fn test_3() {
        assert_eq!(gcd(4, 10), 2);
    }
    #[test]
    fn test_4() {
        assert_eq!(gcd(4, 4), 4);
    }
}
