mod user;
fn main() {
    let mut user1 = user::User {
        username: String::from("username"),
        email: String::from("email@email.com"),
        sign_in_count: 10,
        active: true,
    };

    println!("{:#?}", user1);

    // mutate a field as long as struct is `mut`
    user1.email = String::from("anotheremail@example.com");

    // we can use struct update syntax to create a new instance from an old one.
    let user2 = user::User {
        email: String::from("another@example.com"),
        username: String::from("another"),
        active: user1.active,
        sign_in_count: user1.sign_in_count,
    };

    println!("{:#?}", user2);

    // using the spread syntax.
    let user3 = user::User {
        email: String::from("3rd@example.com"),
        username: String::from("anotherusername"),
        ..user1
    };

    println!("{:#?}", user3);

    // use the build_user function
    let user4 = user::build_user(String::from("new"), String::from("new_email@email.com"));

    println!("{:#?}", user4);

    // using tuple structs without named fields
    #[derive(Debug)]
    struct Color(i32, i32, i32);
    #[derive(Debug)]
    struct Point(i32, i32, i32);

    let black = Color(0, 0, 0);
    let origin = Point(0, 0, 0);

    println!("{:#?}", black);
    println!("{:#?}", origin);

    // there are structs that are the unit type
    let unit_struct = ();

    println!("{:#?}", unit_struct);

    // We could define the struct without owned types (&str)
}
