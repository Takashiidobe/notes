pub fn old_match() {
    let some_u8_value = Some(0u8);

    match some_u8_value {
        Some(3) => println!("Three"),
        _ => (),
    }
}

// use if let to shorten
pub fn if_let_fn() {
    let some_u8_value = Some(0u8);

    if let Some(3) = some_u8_value {
        println!("three");
    }
}

// use if let with an else
pub fn if_let_with_else() {
    let some_u8_value = Some(0u8);

    if let Some(3) = some_u8_value {
        println!("three");
    } else {
        println!("not three");
    }
}
