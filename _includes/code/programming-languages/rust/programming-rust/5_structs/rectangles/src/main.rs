fn main() {
    let width1 = 30;
    let height1 = 50;

    // there is no relation between the two parameters, which isn't great.
    fn area(width: u32, height: u32) -> u32 {
        width * height
    }
    println!(
        "The area of the rectangle is {} square pixels.",
        area(width1, height1)
    );

    let rect1 = (30, 50);
    // using a tuple clarifies the relationship, but indexing into a tuple is unclear.
    fn tuple_area(dimensions: (u32, u32)) -> u32 {
        dimensions.0 * dimensions.1
    }

    println!(
        "The area of the rectangle is {} square pixels.",
        tuple_area(rect1)
    );

    // using a struct
    #[derive(Debug)]
    struct Rectangle {
        width: u32,
        height: u32,
    }

    let rect1 = Rectangle {
        width: 30,
        height: 50,
    };

    println!(
        "The area of the rectangle is {} square pixels.",
        struct_area(&rect1)
    );

    // we borrow so that rect1 is still live afterwards.
    fn struct_area(rectangle: &Rectangle) -> u32 {
        rectangle.width * rectangle.height
    }

    println!("rect1 is {:?}", rect1);

    // using method syntax, define the method of area in the impl for the rectangle

    impl Rectangle {
        fn area(&self) -> u32 {
            self.width * self.height
        }
        fn can_hold(&self, other: &Rectangle) -> bool {
            self.width > other.width && self.height > other.height
        }
    }

    // call a method on the struct
    println!(
        "The area of the rectangle is {} square pixels.",
        rect1.area()
    );

    // note that rust does automatic derefencing here, so there is no need for a `->` operator..
    // methods with more parameters
    let rect1 = Rectangle {
        width: 30,
        height: 50,
    };
    let rect2 = Rectangle {
        width: 10,
        height: 40,
    };
    let rect3 = Rectangle {
        width: 60,
        height: 45,
    };

    println!("Can rect1 hold rect2? {}", rect1.can_hold(&rect2));
    println!("Can rect1 hold rect3? {}", rect1.can_hold(&rect3));
    // you can also add associated functions in an impl, which do not take &self.
    impl Rectangle {
        fn square(size: u32) -> Rectangle {
            Rectangle {
                width: size,
                height: size,
            }
        }
    }

    let square1 = Rectangle::square(10);

    println!("{:?}", square1);
}
