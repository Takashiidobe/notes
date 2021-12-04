fn fizzbuzz(i: u32) -> String {
    match (i % 5, i % 3) {
        (0, 0) => String::from("FizzBuzz"),
        (_, 0) => String::from("Fizz"),
        (0, _) => String::from("Buzz"),
        (_, _) => format!("{}", i),
    }
}
fn main() {
    for i in 1..=100 {
        println!("{}", fizzbuzz(i));
    }
}
