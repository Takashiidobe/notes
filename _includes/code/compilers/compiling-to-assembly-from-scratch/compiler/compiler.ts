//@ts-nocheck

// The interface that each node will conform to.
interface AST {
  equals(other: AST): boolean;
}

// Number is for unsigned integers.
class Number implements AST {
  constructor(public value: number) {}

  equals(other: AST) {
    return true;
  }
}

// Id is for Variables.
class Id implements AST {
  constructor(public value: string) {}

  equals(other: AST) {}
}

// Negation is the infix `!` operator
class Not implements AST {
  constructor(public term: AST) {}

  equals(other: AST) {}
}

// The `==` operator
class Equal implements AST {
  constructor(public left: AST, public right: AST) {}

  equals(other: AST) {}
}

// The `!=` operator
class NotEqual implements AST {
  constructor(public left: AST, public right: AST) {}

  equals(other: AST) {}
}

// Addition
class Add implements AST {
  constructor(public left: AST, public right: AST) {}

  equals(other: AST) {}
}

// Subtraction
class Subtract implements AST {
  constructor(public left: AST, public right: AST) {}

  equals(other: AST) {}
}

// Multiplication
class Multiply implements AST {
  constructor(public left: AST, public right: AST) {}

  equals(other: AST) {}
}

// Division
class Divide implements AST {
  constructor(public left: AST, public right: AST) {}

  equals(other: AST) {}
}

// The function call AST
class Call implements AST {
  constructor(public callee: string, public args: Array<AST>) {}

  equals(other: AST) {
    return (
      other instanceof Call &&
      this.callee == other.callee &&
      this.args.length == other.args.length &&
      this.args.every((arg, i) => arg.equals(other.args[i]))
    );
  }
}

// a return value
class Return implements AST {
  constructor(public term: AST) {}

  equals(other: AST) {}
}

// a block delimited with curly braces.
class Block implements AST {
  constructor(public statements: Array<AST>) {}

  equals(other: AST) {}
}

// A conditional that is evaluated.
class If implements AST {
  constructor(
    public conditional: AST,
    public consequence: AST,
    public alternative: AST
  ) {}

  equals(other: AST) {
    return conditional ? consequence : alternative;
  }
}

// Function bodies
class Function implements AST {
  constructor(
    public name: string,
    public parameters: Array<String>,
    public body: AST
  ) {}

  equals(other: AST) {}
}

// Variable declarations
class Var implements AST {
  constructor(public name: string, public value: AST) {}

  equals(other: AST) {}
}

// Assignment Operator
class Assign implements AST {
  constructor(public name: string, public value: AST) {}

  equals(other: AST) {}
}

// While loop node
class While implements AST {
  constructor(public conditional: AST, public body: AST) {}

  equals(other: AST) {}
}
