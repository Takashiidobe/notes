fn main() {
    let mut v: Vec<i32> = Vec::new();

    v.push(5);
    v.push(6);
    v.push(7);
    v.push(8);

    // vectors drop their elements when the vector goes out of scope.
    {
        let v = vec![1, 2, 3, 4];
        // v is live here
    } // <- v goes out of scope and is freed here.

    let v_ints = vec![1, 2, 3];
}

fn reading_elements_of_vectors() {
    let v = vec![1, 2, 3, 4, 5];

    let third: &i32 = &v[2];
    println!("The third element is: {}", third);

    // get does bounds checking, which returns a result.
    // indexing into the vec with [] does not, and returns a panic if you go outside the vector.
    match v.get(2) {
        Some(third) => println!("The third element is {}", third),
        None => println!("There is no third element"),
    }
}

// trying to push to a vector when you have taken a reference from it won't compile
fn wont_compile() {
    let mut v = vec![1, 2, 3, 4, 5];

    let first = &v[0];

    v.push(6);

    // this wont compile
    // println!("{}", first);
}

// iteration
fn iteration() {
    let v = vec![100, 32, 57];

    for i in &v {
        println!("{}", i);
    }

    // mutable references for mutation
    let mut mut_vec = vec![100, 32, 57];

    for i in &mut mut_vec {
        *i += 50;
    }
}

// we can use a vector to store enums which can store different typed data.
fn enum_vec() {
    enum SpreadsheetCell {
        Int(i32),
        Float(f64),
        Text(String),
    }

    let row = vec![
        SpreadsheetCell::Int(3),
        SpreadsheetCell::Text(String::from("blue")),
        SpreadsheetCell::Float(10.12),
    ];
}
