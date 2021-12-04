fn algorithm(result: &mut Vec<Vec<u64>>, nums: Vec<u64>, begin: usize) {
    match begin == nums.len() {
        true => result.push(nums),
        _ => {
            for i in begin..nums.len() {
                let mut nums = nums.clone();
                nums.swap(begin, i);
                algorithm(result, nums, begin + 1);
            }
        }
    }
}

#[test]
fn test_1() {
    let mut result = vec![];
    algorithm(&mut result, vec![1, 2, 3], 0);
    let mut answer = vec![
        vec![1, 2, 3],
        vec![1, 3, 2],
        vec![2, 1, 3],
        vec![2, 3, 1],
        vec![3, 2, 1],
        vec![3, 1, 2],
    ];
    answer.sort();
    result.sort();
    assert_eq!(result, answer);
}
