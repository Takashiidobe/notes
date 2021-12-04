enum Vehicle {
    Ship(i32, String, String),
    Car(i32, String, String),
}

impl Vehicle {
    fn new_ship(speed: i32, name: String, destination: String) -> Vehicle {
        Vehicle::Ship(speed, name, destination)
    }
    fn new_car(speed: i32, name: String, destination: String) -> Vehicle {
        Vehicle::Car(speed, name, destination)
    }
}

trait VehicleLike {
    fn go(&self) -> String;
}

impl VehicleLike for Vehicle {
    fn go(&self) -> String {
        match &self {
            Vehicle::Ship(speed, _, _) => format!("Going at {} miles per hour by sea.", speed),
            Vehicle::Car(speed, _, _) => format!("Going at {} miles per hour by land.", speed),
            _ => unreachable!(),
        }
    }
}

fn main() {
    for i in 1..1000 {
        let s: Vehicle = Vehicle::new_ship(10, "name".to_string(), "destination".to_string());
        println!("{}", s.go());
        let c: Vehicle = Vehicle::new_car(55, format!("car"), format!("iowa"));
        println!("{}", c.go());
    }
}
