use utils::Scanner;

pub fn algorithm(matrix: &mut Vec<Vec<char>>) -> usize {
    let mut rooms: usize = 0;

    for i in 0..matrix.len() {
        for j in 0..matrix[0].len() {
            if matrix[i][j] == '.' {
                rooms += 1;
                traverse((i, j), matrix);
            }
        }
    }
    rooms
}

fn traverse(coords: (usize, usize), matrix: &mut Vec<Vec<char>>) {
    let (x, y) = coords;

    if matrix[x][y] != '.' {
        return;
    }
    matrix[x][y] = '#';

    if x > 0 {
        traverse((x - 1, y), matrix);
    }
    if x < matrix.len() - 1 {
        traverse((x + 1, y), matrix);
    }
    if y > 0 {
        traverse((x, y - 1), matrix);
    }
    if y < matrix[0].len() - 1 {
        traverse((x, y + 1), matrix);
    }
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let _: u32 = scanner.token();
    let _: u32 = scanner.token();
    let mut rooms: Vec<Vec<char>> = scanner.get_matrix();

    let total = algorithm(&mut rooms);

    println!("{}", total);
}

// #[test]
// fn test_1() {
//     assert_eq!(algorithm(3), 8);
// }
