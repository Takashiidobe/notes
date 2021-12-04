fn algorithm() -> usize {
    let matrix = vec![
        vec![false, false, false, false],
        vec![false, false, false, false],
        vec![false, false, false, false],
        vec![false, false, false, false],
    ];
    let mut count = 0;
    for i in 0..4 {
        for j in 0..4 {
            let mut matrix = matrix.clone();
            if is_valid(matrix, 0) {
                count += 1;
            }
        }
    }
    count
}

fn is_valid(mut matrix: Vec<Vec<bool>>, queens: usize) -> bool {
    if queens == 4 {
        return true;
    }
    for i in 0..matrix.len() {
        for j in 0..matrix[0].len() {
            if !matrix[i][j] {
                dfs(&mut matrix, i, j);
                return is_valid(matrix, queens + 1);
            }
        }
    }

    false
}

fn dfs(matrix: &mut Vec<Vec<bool>>, x: usize, y: usize) {
    for i in 0..matrix.len() {
        for j in 0..matrix[0].len() {
            if i == x || j == y {
                matrix[i][j] = true;
            }
            if i > x && j > y && i - x == j - y {
                matrix[i][j] = true;
            }
            if i + x < matrix.len() && j + y < matrix[0].len() && i + x == j + y {
                matrix[i][j] = true;
            }
        }
    }
}

#[test]
fn two_queens() {
    assert_eq!(algorithm(), 2);
}
