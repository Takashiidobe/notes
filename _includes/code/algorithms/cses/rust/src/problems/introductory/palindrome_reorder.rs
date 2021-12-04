// use utils::Scanner;
// use std::collections::HashMap;

// pub fn algorithm(s: String) -> Option<String> {
//     // check the string length
//     // if even, all characters must appear % 2 times.
//     // if odd, one character may appear % 2 != 0 times, but the rest must.
//     // otherwise, randomly put characters in a string at the ends,
//     // if odd, place the lone % 2 != 0 char in the middle, the rest can go at the ends.
//     let is_even = if s.len() % 2 == 0 { true } else { false };

//     let mut hm = HashMap::new();
//     // iterate through string.
//     for c in s.chars() {
//         *hm.entry(c).or_insert(0) += 1;
//     }

//     if is_even {
//         for (_, value) in hm.into_iter() {
//             if value % 2 != 0 {
//                 return None;
//             }
//         }
//     } else {
//         let mut odd_occurrences_allowed = true;
//         for (_, value) in hm.into_iter() {
//             if value % 2 == 0 {
//                 continue;
//             }
//             if odd_occurrences_allowed == true {
//                 odd_occurrences_allowed = false;
//             } else {
//                 return None;
//             }
//         }
//     }

//     // start putting random characters at the end and join to Some String.

//     None
// }

// #[allow(dead_code)]
// pub fn answer() {
//     let stdin = std::io::stdin();
//     let mut scanner = Scanner::new(stdin.lock());

//     let input = scanner.get_line();

//     match algorithm(input) {
//         Some(v) => println!("{}", v),
//         None => println!("NO SOLUTION"),
//     }
// }

// #[test]
// fn test_1() {
//     assert_eq!(algorithm(2, 1), true);
// }
// #[test]
// fn test_2() {
//     assert_eq!(algorithm(2, 2), false);
// }

// #[test]
// fn test_3() {
//     assert_eq!(algorithm(3, 3), true);
// }
// #[test]
// fn test_4() {
//     assert_eq!(algorithm(4, 4), false);
// }
