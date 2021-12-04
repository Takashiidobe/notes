use std::fmt;

#[macro_export]
macro_rules! myvec {
    ( $( $x:expr), *) => {
       let mut temp_vec = Vec::new();
       $(
            temp_vec.push($x)
       )*
       temp_vec
    };
}

struct Password<'a>(&'a str);

impl fmt::Display for Password<'_> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "********")
    }
}

impl fmt::Debug for Password<'_> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "********")
    }
}

fn main() {
    let pass = Password("super secret password");
    println!("{}", pass);
    println!("{:?}", pass);
    let string = "blah";
    println!("{}", string);
}
