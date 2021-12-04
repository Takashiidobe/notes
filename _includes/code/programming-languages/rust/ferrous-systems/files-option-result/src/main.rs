use std::fs::{read_to_string, File};
use std::io::prelude::*;

fn task_one() {
    let f = File::open("./data/context.txt");
    match f {
        Ok(file) => println!("File Opened: {:?}", file),
        Err(e) => println!("Error! {:?}", e),
    }
}

fn task_two() {
    let f = File::open("./data/context.txt");
    let s = read_to_string("./data/context.txt");
}

fn main() {}
