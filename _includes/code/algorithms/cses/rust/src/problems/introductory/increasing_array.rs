use utils::Scanner;

pub fn algorithm(mut nums: Vec<u64>) -> u64 {
    let mut total = 0;

    let mut i = 0;
    let mut j = 1;

    while j < nums.len() {
        if nums[i] > nums[j] {
            total += nums[i] - nums[j];
            nums[j] = nums[i];
        }

        i += 1;
        j += 1;
    }

    total
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let _: usize = scanner.token();
    let nums = scanner.get_spaced_line_vec();

    let total = algorithm(nums);

    println!("{:?}", total);
}

#[test]
fn test_1() {
    assert_eq!(
        algorithm(vec![1000000000, 1, 1, 1, 1, 1, 1, 1, 1, 1]),
        8999999991
    );
}
#[test]
fn test_2() {
    assert_eq!(algorithm(vec![3, 2, 5, 1, 7]), 5);
}

#[test]
fn test_3() {
    assert_eq!(algorithm(vec![6, 10, 4, 10, 2, 8, 9, 2, 7, 7]), 31);
}
