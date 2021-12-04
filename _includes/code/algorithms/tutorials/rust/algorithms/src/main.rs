fn main() {
    let v = (1..).take(20).collect::<Vec<i32>>();

    // first, we want to print out the vector.
    for x in v.iter().cloned() {
        print!("{} ", x);
    }

    // filter out only the evens and print them
    let filtered = v.iter().cloned().filter(|x| x % 2 == 0);

    for x in filtered {
        print!("{} ", x);
    }

    let squared_evens = v.iter().cloned().map(|x| x * x).filter(|x| x % 2 == 0);

    for x in squared_evens {
        print!("{} ", x);
    }

    // sum all even squared numbers
    let sum_squared_evens: i32 = v
        .iter()
        .cloned()
        .map(|x| x * x)
        .filter(|x| x % 2 == 0)
        .sum();

    println!("{}", sum_squared_evens);
}
