// enum IpAddrKind {
//     V4,
//     V6,
// }
//
// struct IpAddr {
//     kind: IpAddrKind,
//     address: String,
// }
//
// fn route(ip_kind: IpAddrKind) {
//     match ip_kind {
//         IpAddrKind::V4 => println!("This is v4"),
//         IpAddrKind::V6 => println!("This is v6"),
//     }
// }

fn main() {
    // let four = IpAddrKind::V4;
    // let six = IpAddrKind::V6;
    // route(four);
    // route(six);

    // let home = IpAddr {
    //     kind: IpAddrKind::V4,
    //     address: String::from("127.0.0.1"),
    // };

    // let loopback = IpAddr {
    //     kind: IpAddrKind::V6,
    //     address: String::from("::1"),
    // };

    // we can just use an enum for V4 and V6.
    // enum IpAddr {
    //     V4(String),
    //     V6(String),
    // }

    // let home = IpAddr::V4(String::from("127.0.0.1"));
    // let loopback = IpAddr::V6(String::from("::1"));

    // we can even have different types for variants
    // enum IpAddr {
    //     V4(u8, u8, u8, u8),
    //     V6(String),
    // }

    // let home = IpAddr::V4(127, 0, 0, 1);
    // let loopback = IpAddr::V6(String::from("::1"));
    // enum Message {
    //     Quit,
    //     Move { x: i32, y: i32 },
    //     Write(String),
    //     ChangeColor(i32, i32, i32),
    // }

    // // you can impl for your enums as well
    // impl Message {
    //     fn move_around(&self, x: i32, y: i32) {}
    // }

    // // options
    // let x: i8 = 5;
    // let y: Option<i8> = None;

    // // remember to unwrap or check for nulls.
    // let sum = x + y.unwrap_or_default();
    // println!("{}", sum);
}
