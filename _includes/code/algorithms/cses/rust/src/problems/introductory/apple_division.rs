use std::fmt::{Debug, Display};
use std::io;
use std::str::FromStr;

pub struct Scanner<R> {
    reader: R,
    buffer: Vec<String>,
}

impl<R: io::BufRead> Scanner<R> {
    pub fn new(reader: R) -> Self {
        Self {
            reader,
            buffer: vec![],
        }
    }

    pub fn token<T: FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            self.reader.read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }

    pub fn get_spaced_line_vec<T: FromStr>(&mut self) -> Vec<T>
    where
        <T as FromStr>::Err: Debug,
    {
        let mut items = String::new();

        self.reader.read_line(&mut items).ok().expect("read error");

        items
            .split_whitespace()
            .map(|s| s.parse().expect("parse error"))
            .collect()
    }

    pub fn get_line(&mut self) -> String {
        let mut input = String::new();
        self.reader.read_line(&mut input).expect("Failed read");
        input.trim_end().to_string()
    }

    pub fn split_line(&mut self) -> Vec<char> {
        let mut input = String::new();
        self.reader.read_line(&mut input).expect("Failed read");
        input.trim_end().chars().collect()
    }

    pub fn get_matrix(&mut self) -> Vec<Vec<char>> {
        let mut v: Vec<Vec<char>> = vec![];
        let mut input = String::new();
        loop {
            let bytes = self.reader.read_line(&mut input).ok().expect("Read error");
            if bytes == 0 {
                break;
            }
            v.push(input.trim().chars().collect());
            input = String::new();
        }
        v
    }

    pub fn get_line_to_tuple<T: Clone + FromStr>(&mut self) -> (T, T)
    where
        <T as FromStr>::Err: Debug,
        T: Debug,
    {
        let mut items = String::new();

        self.reader.read_line(&mut items).ok().expect("read error");

        let pair: Vec<T> = items
            .split_whitespace()
            .map(|s| s.parse().expect("parse error"))
            .collect();

        (pair[0].clone(), pair[1].clone())
    }
}

pub fn print_vec<T: Display>(v: &Vec<T>) {
    for (index, item) in v.iter().enumerate() {
        print!("{}", item);
        if index != v.len() - 1 {
            print!(" ");
        }
    }
}

pub fn print_matrix<T: Display>(m: &Vec<Vec<T>>) {
    for item in m {
        print_vec(&item);
        print!("\n");
    }
}

#[allow(dead_code)]
pub fn algorithm(input: &Vec<i64>, i: usize, left_sum: i64, right_sum: i64) -> i64 {
    if i >= input.len() {
        return i64::abs(left_sum - right_sum);
    }

    i64::min(
        algorithm(&input, i + 1, left_sum + input[i], right_sum),
        algorithm(&input, i + 1, left_sum, right_sum + input[i]),
    )
}

#[allow(dead_code)]
pub fn main() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let _: usize = scanner.token();
    let input = scanner.get_spaced_line_vec();

    let output = algorithm(&input, 0, 0, 0);

    println!("{:?}", output);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        assert_eq!(algorithm(&vec![3, 2, 7, 4, 1], 0, 0, 0), 1);
    }

    #[test]
    fn test_2() {
        assert_eq!(
            algorithm(
                &vec![952, 775, 292, 702, 859, 719, 65, 943, 376, 490],
                0,
                0,
                0
            ),
            1
        );
    }

    #[test]
    fn test_3() {
        assert_eq!(
            algorithm(
                &vec![
                    934033764, 747013925, 113297529, 621350044, 4858224, 896418401, 823418019,
                    490285020, 811592918, 318107753, 122431099, 971962557, 68572395, 269437889,
                    506050802, 903504371, 908615271, 406858603, 39392057, 816479348
                ],
                0,
                0,
                0
            ),
            5483
        );
    }
}
