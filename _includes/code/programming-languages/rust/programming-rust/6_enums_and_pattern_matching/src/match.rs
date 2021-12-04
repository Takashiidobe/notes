pub enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter(UsState),
}

#[derive(Debug)]
pub enum UsState {
    Alabama,
    Alaska,
}

pub fn value_in_cents(coin: Coin) -> u8 {
    match coin {
        Coin::Penny => {
            println!("Lucky Penny!");
            1
        }
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter => {
            println!("State quarter from {:?}!", state);
            25
        }
    }
}

// matching with Option <T>

pub fn plus_one(x: Option<i32>) -> Option<i32> {
    match x {
        None => None,
        Some(i) => Some(i + 1),
    }
}

// let five = Some(5);
// let six = plus_one(five);
// let none = plus_one(None);

// if we wrote plus_one like this:
// pub fn plus_one(x: Option<i32>) -> Option<i32> {
//      match x {
//          Some(i) => Some(i + 1),
//          // this won't compile because we missed the None case.
//      }
// }
