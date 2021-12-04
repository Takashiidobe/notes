use std::cmp::PartialOrd;

#[allow(dead_code)]
fn binary_search<T: PartialOrd>(arr: Vec<T>, target: T) -> Option<usize> {
    let mut lower: usize = 0;
    let mut upper: usize = arr.len();

    while lower < upper {
        let mid: usize = lower + (upper - lower) / 2;

        if arr[mid] == target {
            return Some(mid);
        } else if arr[mid] > target {
            upper = mid - 1;
        } else {
            lower = mid + 1;
        }
    }

    None
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_match() {
        assert_eq!(binary_search::<i32>(vec![1, 2, 3, 4], 4), Some(3));
    }

    #[test]
    fn test_none() {
        assert_eq!(binary_search::<i32>(vec![1, 2, 3, 4], 6), None);
    }

    #[test]
    fn test_empty() {
        assert_eq!(binary_search::<i32>(vec![], 4), None);
    }
}
