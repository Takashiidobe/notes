class Animal:
    def name(self):
        return "Animal"

    def move(self):
        print(f"walk {self.name()}")


class Bird(Animal):
    def name(self):
        return "Bird"

    def move(self):
        print(f"fly {self.name()}")


class Elephant(Animal):
    def name(self):
        return "Elephant"


def main():
    animals = [Animal(), Bird(), Elephant()]
    for animal in animals:
        animal.move()


if __name__ == "__main__":
    main()
