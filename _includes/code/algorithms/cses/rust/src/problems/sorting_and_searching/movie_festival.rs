use utils::Scanner;

pub fn algorithm(mut movies: Vec<(u64, u64)>) -> u64 {
    movies.sort_by(|left, right| left.1.partial_cmp(&right.1).unwrap());
    let mut ans = 0;
    let mut curr_event_end = 0;
    for (start, end) in movies {
        if start >= curr_event_end {
            ans += 1;
            curr_event_end = end;
        }
    }
    ans
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let count: usize = scanner.token();

    let mut movies = vec![];

    for _ in 0..count {
        movies.push(scanner.get_line_to_tuple());
    }

    println!("{}", algorithm(movies));
}

#[test]
fn test_1() {
    assert_eq!(algorithm(vec![(3, 5), (4, 9), (5, 8)]), 2);
}
