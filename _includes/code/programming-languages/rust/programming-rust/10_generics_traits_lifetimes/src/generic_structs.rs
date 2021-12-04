// generic struct
struct Point<T> {
    x: T,
    y: T,
}

struct Point<X, Y> {
    x: X,
    y: Y,
}

// generic enum
enum Result<T, E> {
    Ok(T),
    Err(E),
}

// generic methods
impl<T> Point<T> {
    fn x(&self) -> &T {
        &self.x
    }
}
// impl a function for f32s only
impl Point<f32> {
    fn distance_from_origin(&self) -> f32 {
        (self.x.powi(2) + self.y.powi(2)).sqrt()
    }
}

fn main() {
    let integer = Point { x: 5, y: 10 };
    let float = Point { x: 1.0, y: 4.0 };
}

// generics are monomorphized, which turns them into specific structs/options and uses them.
