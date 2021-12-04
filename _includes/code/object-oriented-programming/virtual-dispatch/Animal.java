public class Animal {
  void move() {
    System.out.printf("walk %s\n", this.name());
  }

  String name() {
    return "Animal";
  }
  public static void main(String[] args) {
    Animal animals[] = {new Animal(), new Bird(), new Elephant()};

    for (Animal animal : animals) {
      animal.move();
    }
    var bird = new Bird();
    bird.move();
  }
}

class Bird extends Animal {
  @Override
  void move() {
    System.out.printf("fly %s\n", this.name());
  }

  @Override
  String name() {
    return "Bird";
  }
}

class Elephant extends Animal {
  @Override
  String name() {
    return "Elephant";
  }
}