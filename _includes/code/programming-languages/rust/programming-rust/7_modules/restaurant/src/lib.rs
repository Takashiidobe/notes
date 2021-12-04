mod front_of_house;

pub use crate::front_of_house::hosting;

pub fn eat_at_restaurant() {
    hosting::add_to_waitlist();
    hosting::add_to_waitlist();
    hosting::add_to_waitlist();
}

// mod front_of_house {
//     pub mod hosting {
//         pub fn add_to_waitlist() {}
//
//         fn seat_at_table() {}
//     }
//
//     mod serving {
//         fn take_order() {}
//
//         fn serve_order() {}
//
//         fn take_payment() {}
//     }
// }
//
// pub fn serve_order() {}
//
// mod back_of_house {
//     pub enum Appetizer {
//         Soup,
//         Salad,
//     }
//     pub struct Breakfast {
//         pub toast: String,
//         seasonal_fruit: String,
//     }
//
//     impl Breakfast {
//         pub fn summer(toast: &str) -> Breakfast {
//             Breakfast {
//                 toast: String::from(toast),
//                 seasonal_fruit: String::from("Peaches"),
//             }
//         }
//     }
//
//     fn fix_incorrect_order() {
//         cook_order();
//         super::serve_order();
//     }
//
//     fn cook_order() {}
// }
//
// // calling functions
//
// // use `use` to shorten a path.
//
// use front_of_house::hosting;
//
// // we can use as to alias imports
// use std::io::Result as IoResult;
//
// // we can also reexport a name from another scope publically using pub use
//
// // instead of
// // use std::io;
// // use std::io::Write;
// //
// // we can write:
// // use std::io::{self, Write};
// // use std::collections::*;
//
// pub use crate::back_of_house::Appetizer;
//
// pub fn eat_at_restaurant() {
//     let mut meal = back_of_house::Breakfast::summer("Rye");
//
//     meal.toast = String::from("Wheat");
//
//     let order1 = back_of_house::Appetizer::Soup;
//     let order2 = back_of_house::Appetizer::Salad;
//
//     hosting::add_to_waitlist();
//     hosting::add_to_waitlist();
//     hosting::add_to_waitlist();
//
//     println!("I'd like {} toast please", meal.toast);
// }
