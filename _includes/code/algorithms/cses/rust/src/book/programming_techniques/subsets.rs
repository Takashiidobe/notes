fn algorithm(nums: Vec<u64>) -> Vec<Vec<u64>> {
    let mut answer = vec![vec![]];
    for num in nums {
        let mut temp = answer.clone();
        for n in &mut temp {
            n.push(num);
        }
        answer.append(&mut temp);
    }
    answer
}

#[test]
fn test_1() {
    assert_eq!(
        algorithm(vec![1, 2, 3]),
        vec![
            vec![],
            vec![1],
            vec![2],
            vec![1, 2],
            vec![3],
            vec![1, 3],
            vec![2, 3],
            vec![1, 2, 3]
        ]
    );
}

#[test]
fn test_2() {
    assert_eq!(algorithm(vec![0]), vec![vec![], vec![0]]);
}
