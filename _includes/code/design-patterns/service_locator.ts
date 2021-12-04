class CoffeeStore {
  constructor(private instance_?: Coffee) {}
  bind(instance: Coffee) {
    this.instance_ = instance;
  }
  getCoffee(): string {
    if (this.instance_) {
      return this.instance_.getCoffee();
    } else {
      return new NullCoffee().getCoffee();
    }
  }
}

type Coffee = {
  getCoffee(): string;
};

class NullCoffee implements Coffee {
  getCoffee() {
    return "Null Coffee";
  }
  constructor() {}
}

class RealCoffee implements Coffee {
  getCoffee() {
    return "Real Coffee";
  }
  constructor() {}
}

class MockClass {
  constructor() {}
}

const cs = new CoffeeStore(new CoffeeStore());

console.log(cs.getCoffee());
