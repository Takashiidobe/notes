pub trait Animal {
    fn name(&self) -> String {
        "Animal".to_string()
    }
    fn act(&self) {
        println!("walk {}", self.name());
    }
}

struct GenericAnimal {}
impl Animal for GenericAnimal {}

struct Bird {}
impl Animal for Bird {
    fn name(&self) -> String {
        "Bird".to_string()
    }
    fn act(&self) {
        println!("fly {}", self.name());
    }
}

struct Elephant {}
impl Animal for Elephant {
    fn name(&self) -> String {
        "Elephant".to_string()
    }
}


fn main() {
    let animals: Vec<&dyn Animal> = vec![&GenericAnimal{}, &Bird{}, &Elephant{}];
    for animal in animals {
        animal.act();
    }
}
