use utils::Scanner;

pub fn algorithm(matrix: &mut Vec<Vec<char>>) -> Option<String> {
    let _rooms: usize = 0;
    let mut paths = vec![];

    for i in 0..matrix.len() {
        for j in 0..matrix[0].len() {
            if matrix[i][j] == 'A' {
                let path = traverse((i, j), matrix, &mut String::new());
                println!("{:?}", &path);
                paths.push(path);
            }
        }
    }
    Some(String::new())
}

fn traverse(
    coords: (usize, usize),
    matrix: &mut Vec<Vec<char>>,
    path: &mut String,
) -> Option<String> {
    let (x, y) = coords;

    if matrix[x][y] == '#' {
        return None;
    }
    if matrix[x][y] == 'B' {
        return Some(path.to_string());
    }

    if x > 0 {
        path.push('L');
        traverse((x - 1, y), matrix, path);
    }
    if x < matrix.len() - 1 {
        path.push('R');
        traverse((x + 1, y), matrix, path);
    }
    if y > 0 {
        path.push('U');
        traverse((x, y - 1), matrix, path);
    }
    if y < matrix[0].len() - 1 {
        path.push('D');
        traverse((x, y + 1), matrix, path);
    }
    None
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let _: u32 = scanner.token();
    let _: u32 = scanner.token();
    let mut rooms: Vec<Vec<char>> = scanner.get_matrix();

    let total = algorithm(&mut rooms);

    println!("{:?}", total);
}

// #[test]
// fn test_1() {
//     assert_eq!(algorithm(3), 8);
// }
