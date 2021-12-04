use utils::Scanner;

pub fn algorithm(blocks: Vec<usize>) -> usize {
    if blocks.len() < 1 {
        return 0;
    }
    let mut towers = vec![];
    towers.push(&blocks[0]);
    for block in blocks.iter().skip(1) {
        if block > towers.last().unwrap() {
            towers.push(block);
        }
        let mut low = 0;
        let mut high = towers.len();
        while low < high {
            let mid = (low + high) / 2;
            if towers[mid] > block {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        if low == towers.len() {
            towers.push(block);
        } else {
            towers[low] = block;
        }
    }
    // iterate through the towers and find the one with smallest diff.
    // stick block on top of tower.
    towers.len()
}

#[allow(dead_code)]
pub fn answer() {
    let stdin = std::io::stdin();
    let mut scanner = Scanner::new(stdin.lock());

    let _: usize = scanner.token();
    let blocks: Vec<usize> = scanner.get_spaced_line_vec();

    println!("{}", algorithm(blocks));
}

#[test]
fn test_1() {
    assert_eq!(algorithm(vec![3, 8, 2, 1, 5]), 5);
}
