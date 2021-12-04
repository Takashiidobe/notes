const MAX_POINTS: u32 = 100_000;

// we can mutate a mutable variable's value but not its type
// we can shadow a variables type and value.

/// There four primary scalar types
/// Integers, Floats, Booleans, Characters.
/// Length	Signed	Unsigned
/// 8-bit	i8	u8
/// 16-bit	i16	u16
/// 32-bit	i32	u32
/// 64-bit	i64	u64
/// 128-bit	i128	u128
/// arch	isize	usize

fn main() {
    let guess: u32 = "42".parse().expect("not a number!");

    let f = 2.0; // f64 -> default
    let y: f32 = 3.0; //f32

    let sum = 5 + 10; // i32
    let difference = 95.5 - 4.3; // f64
    let product = 3 * 30; // i32
    let quotient = 56.7 / 32.2; // f64
    let remainder = 43 % 5; // i32

    let t = true;
    let f: bool = false;

    let c = 'z';
    let z = 'ℤ';
    let heart_eyed_cat = '😻';

    let x = 5;
    println!("The value of x is: {}", x);
    let x = 6;
    println!("The value of x is: {}", x);

    // Compound types
    // Tuples
    // Tuples need not have the same types for all elements.
    let tup: (i32, f64, u8) = (500, 6.4, 1);
    let random_tup: (char, String, u8) = ('c', "Hello".to_string(), 255);

    let (x, y, z) = tup; // x = 500, y = 6.4, z = 1;

    // Tuple access is done with .index
    let five_hundred = tup.0;
    let six_point_four = tup.1;
    let one = tup.2;

    // Arrays
    // Arrays are a comma separated list of items with the same type enclosed in square brackets
    let a: [i32; 5] = [1, 2, 3, 4, 5];

    // you can also create a list with the same elements faster.
    // This has the value 3 5 times.
    let a = [3; 5];
}
