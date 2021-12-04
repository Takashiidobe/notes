mod slice;

fn main() {
    let mut s = String::from("hello");
    s.push_str(", world!");

    let s1 = String::from("hello");
    let s2 = s1;

    println!("{}", s2);

    let x = 5;
    let y = x; // this is a copy, on the stack.

    // this is a stack and heap copy (clone).
    let s3 = String::from("hello");
    let s4 = s2.clone();

    let mut s = String::from("hello world");

    let word = slice::first_word(&s);

    s.clear(); // empty the string.
}
