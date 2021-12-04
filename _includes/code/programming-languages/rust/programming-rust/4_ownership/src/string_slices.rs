fn string_slices() -> (&str, &str) {
    let s = String::from("hello world");

    let hello = &s[0..5];
    let world = &s[6..11];

    (hello, world)
}

// rewriting first_word to return a slice with the correct chars
fn first_word(s: &String) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }

    &s[..]
}

// string literals like
// let s = "Hello, world!"; are of type &str.
