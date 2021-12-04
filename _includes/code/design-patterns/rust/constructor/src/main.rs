use std::fmt::{Display, Formatter, Result};

/// As rust does not have a constructor, you generally create a static new method to create an
/// object

#[derive(Debug)]
pub struct Person {
    name: String,
    age: u8,
}

impl Person {
    pub fn new(name: String, age: u8) -> Person {
        Person { name, age }
    }
}

impl Display for Person {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result {
        write!(f, "My name is: {}, and my age is: {}", self.name, self.age)
    }
}

fn main() {
    let person = Person::new("Person".to_string(), 18);
    println!("{}", person);
}
