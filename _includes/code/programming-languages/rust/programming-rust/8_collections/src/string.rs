fn string_creation() {
    let mut s = String::new();

    // &str
    let data = "intiial_contents";

    // &str -> String
    let s = data.to_string();

    let s1 = String::from("intiial_contents");

    // we can push strings to append to a string slice.
    let mut s = String::from("foo");
    s.push_str("bar");

    // we can push a char
    let mut char_push = String::from("Lo");
    char_push.push('l');

    // we can combine two strings (this takes ownership)
    let s1 = String::from("Hello, ");
    let s2 = String::from("world!");
    let s3 = s1 + &s2; // note s1 has been moved here and can no longer be used

    // we can use the format! macro to concatenate strings as well.
    // format! doesn't take ownership.

    let s1 = String::from("tic");
    let s2 = String::from("tac");
    let s3 = String::from("toe");

    let s = format!("{}-{}-{}", s1, s2, s3);

    // rust allows you to index into a string as chars (u8s), as scalars, or as grapheme
    // clusters

    // use .chars() to iterate over the chars.
    for c in "नमस्ते".chars() {
        println!("{}", c);
    }

    // use .bytes() to print out the byte numbers
    for b in "नमस्ते".bytes() {
        println!("{}", b);
    }

    // use crates.io to get the grapheme clusters
}
