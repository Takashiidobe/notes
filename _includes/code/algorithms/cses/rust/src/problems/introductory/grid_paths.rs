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

const SIZE: usize = 7;
static mut VISITED: &mut [[bool; SIZE]; SIZE] = &mut [[false; SIZE]; SIZE];
static mut ANS: usize = 0;

#[allow(dead_code)]
pub fn algorithm(directions: &Vec<char>, r: usize, c: usize, steps: usize) {
    unsafe {
        // if valid path, add to answer, return.
        if steps == SIZE * SIZE - 1 {
            if r == SIZE - 1 && c == 0 {
                ANS += 1;
            }
            return;
        }

        // if we are at the southern most row
        // if we cannot go up again
        // let first = r + 1 == SIZE
        //     || r > 0
        //         && c > 0
        //         && c < SIZE - 1
        //         && r < SIZE - 1
        //         && VISITED[r - 1][c]
        //         && VISITED[r + 1][c]
        //         && !VISITED[r][c - 1]
        //         && !VISITED[r][c + 1];

        // let second = c + 1 == SIZE
        //     || r > 0
        //         && c > 0
        //         && c < SIZE - 1
        //         && r < SIZE - 1
        //         && VISITED[r][c - 1]
        //         && VISITED[r][c + 1]
        //         && !VISITED[r - 1][c]
        //         && !VISITED[r + 1][c];

        // if first || second {
        //     return;
        // }

        VISITED[r][c] = true;
        if directions[steps] != '?' {
            if directions[steps] == 'U' {
                if r > 0 && !VISITED[r - 1][c] {
                    algorithm(&directions, r - 1, c, steps + 1);
                }
            }

            if directions[steps] == 'D' {
                if r < SIZE - 1 && !VISITED[r + 1][c] {
                    algorithm(&directions, r + 1, c, steps + 1);
                }
            }

            if directions[steps] == 'R' {
                if c < SIZE - 1 && !VISITED[r][c + 1] {
                    algorithm(&directions, r, c + 1, steps + 1);
                }
            }

            if directions[steps] == 'L' {
                if c > 0 && !VISITED[r][c - 1] {
                    algorithm(&directions, r, c - 1, steps + 1);
                }
            }
            VISITED[r][c] = false;
            return;
        } else {
            // down
            if r < SIZE - 1 && !VISITED[r + 1][c] {
                algorithm(&directions, r + 1, c, steps + 1);
            }
            // right
            if c < SIZE - 1 && !VISITED[r][c + 1] {
                algorithm(&directions, r, c + 1, steps + 1);
            }
            // up
            if r > 0 && !VISITED[r - 1][c] {
                algorithm(&directions, r - 1, c, steps + 1);
            }
            // left
            if c > 0 && !VISITED[r][c - 1] {
                algorithm(&directions, r, c - 1, steps + 1);
            }
        }
        VISITED[r][c] = false;
    }
}

#[allow(dead_code)]
pub fn main() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let input: Vec<char> = scanner.get_line().chars().collect();

    algorithm(&input, 0, 0, 0);

    unsafe {
        println!("{:?}", &ANS);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        let input: Vec<char> = "????U???????????D???????????????????????????????"
            .chars()
            .collect();
        unsafe {
            ANS = 0;
        }
        algorithm(&input, 0, 0, 0);
        unsafe {
            assert_eq!(ANS, 6665);
        }
    }

    #[test]
    fn test_2() {
        let input: Vec<char> = "????D???L??D?L??????????????R??D???????????D??RD"
            .chars()
            .collect();
        unsafe {
            ANS = 0;
        }
        algorithm(&input, 0, 0, 0);
        unsafe {
            assert_eq!(ANS, 0);
        }
    }

    #[test]
    fn test_3() {
        let input: Vec<char> = "??????????????????UL????U?L??L?D???RR???????????"
            .chars()
            .collect();
        unsafe {
            ANS = 0;
        }
        algorithm(&input, 0, 0, 0);
        unsafe {
            assert_eq!(ANS, 1);
        }
    }

    #[test]
    fn test_4() {
        let input: Vec<char> = "???????????????????????????????????????????????D"
            .chars()
            .collect();
        unsafe {
            ANS = 0;
        }
        algorithm(&input, 0, 0, 0);
        unsafe {
            assert_eq!(ANS, 1);
        }
    }
}
