// use utils::Scanner;

// pub fn algorithm(row: usize, col: usize) -> usize {
//     let max = std::cmp::max(row, col);
//     let min = std::cmp::min(row, col);
//     let mut total = 0;

//     let mut max_possible = 1;

//     for i in (1..max) {
//         max_possible += (2 * i) + 1;
//     }

//     // find out the level and subtract the minimum.
//     // if max % 2 == 0 return max_possible - min + 1
//     // if max % 2 != 0 return max_possible - min + 1
//     let answer = if max % 2 == 0 {
//         // colwise
//         if col == min {
//             max_possible - (max * 2) + 1
//         } else {
//         }
//     } else {
//         // rowwise
//         if col == min {
//         } else {
//         }
//     };
//     answer
// }

// // grab the max of the column and row, and generate up to that many layers.
// // 1 + 3 + 5 + 7 + 9
// // if n % 2 == 0 start at col
// // if n % 2 != 0 start at row

// #[allow(dead_code)]
// pub fn answer() {
//     let stdin = std::io::stdin();
//     let mut scanner = Scanner::new(stdin.lock());

//     let n: usize = scanner.token();

//     let mut coords: Vec<(usize, usize)> = vec![];
//     for i in 0..n {
//         coords.push(scanner.get_line_to_tuple())
//     }
//     algorithm(coords[0].0, coords[0].1);
// }

// #[test]
// fn test_1() {
//     assert_eq!(algorithm(5), Some(vec![1, 3, 5, 2, 4]));
// }
// #[test]
// fn test_2() {
//     assert_eq!(algorithm(3), None);
// }

// #[test]
// fn test_3() {
//     assert_eq!(algorithm(8), Some(vec![8, 6, 4, 2, 7, 5, 3, 1]));
// }
// #[test]
// fn test_4() {
//     assert_eq!(algorithm(4), Some(vec![2, 4, 1, 3]));
// }
