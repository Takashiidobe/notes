//@ts-nocheck
interface Parser<T> {
  parse(Source): ParseResult<T> | null;
}

class Source {
  constructor(public string: string, public index: number) {}

  match(regexp: RegExp): ParseResult<string> | null {
    console.assert(regexp.sticky);
    regexp.lastIndex = this.index;
    let match = this.string.match(regexp);
    if (match) {
      let value = match[0];
      let newIndex = this.index + value.length;
      let source = new Source(this.string, newIndex);
      return new ParseResult(value, source);
    }
    return null;
  }
}

class ParseResult<T> {
  constructor(public value: T, public source: Source) {}
}

class Parser<T> {
  constructor(public parse: (Source) => ParseResult<T> | null) {}

  static regexp(regexp: RegExp): Parser<string> {
    return new Parser((source) => source.match(regexp));
  }

  static constant<U>(value: U): Parser<U> {
    return new Parser((source) => new ParseResult(value, source));
  }

  static error<U>(message: string): Parser<U> {
    return new Parser((source) => {
      throw Error(`Error Index: ${source.index} Error message: ${message}`);
    });
  }

  or(parser: Parser<T>): Parser<T> {
    return new Parser((source) => {
      let result = this.parse(source);
      if (result) return result;
      else return parser.parse(source);
    });
  }

  static zeroOrMore<U>(parser: Parser<U>): Parser<Array<U>> {
    return new Parser((source) => {
      let results = [];
      let item;
      while ((item = parser.parse(source))) {
        source = item.source;
        results.push(item.value);
      }
      return new ParseResult(results, source);
    });
  }

  bind<U>(callback: (value: T) => Parser<U>): Parser<U> {
    return new Parser((source) => {
      let result = this.parse(source);
      if (result) {
        let { value, source } = result;
        return callback(value).parse(source);
      } else {
        return null;
      }
    });
  }

  and<U>(parser: Parser<U>): Parser<U> {
    return this.bind((_) => parser);
  }

  map<U>(callback: (t: T) => U): Parser<U> {
    return this.bind((value) => constant(callback(value)));
  }

  static maybe<U>(parser: Parser<U>): Parser<U | null> {
    return parser.or(constant(null));
  }

  parseStringToCompletion(string: string): T {
    let source = new Source(string, 0);
    let result = this.parse(source);
    if (!result) throw Error("Parse error at index 0");

    let index = result.source.index;
    if (index != result.source.string.length)
      throw Error("Parse error at index " + index);

    return result.value;
  }
}

/*

Chapter 5 notes
let { regexp, constant, error } = Parser;
let source = new Source("hello1 bye2", 0);
let letterOrDigit = regexp(/[a-z]/y).or(regexp(/[0-9]/y));

let hello = regexp(/hello[0-9]/y);
let result = hello.parse(source);

// the parser combinator parses a chunk of hello + [0-9], then tells you the next index.
console.assert(result.value === "hello1");
console.assert(result.source.index === 6);
*/

// Tokens

let { regexp, constant, error } = Parser;

let whitespace = regexp(/[ \n\r\t]+/y);
let comments = regexp(/[/][/].*/y).or(regexp(/[/][*].*[*][/]/sy));
let ignored = zeroOrMore(whitespace.or(comments));

let token = (pattern) =>
  regexp(pattern).bind((value) => ignored.and(constant(value)));

let FUNCTION = token(/function\b/y);
let IF = token(/if\b/y);
let ELSE = token(/else\b/y);
let RETURN = token(/return\b/y);
let VAR = token(/var\b/y);
let WHILE = token(/while\b/y);
let COMMA = token(/[,]/y);
let SEMICOLON = token(/;/y);
let LEFT_PAREN = token(/[(]/y);
let RIGHT_PAREN = token(/[)]/y);
let LEFT_BRACE = token(/[{]/y);
let RIGHT_BRACE = token(/[}]/y);

let NUMBER = token(/[0-9]+/y).map((digits) => newNumber(parseInt(digits)));

let ID = token(/[a-zA-Z_][a-zA-Z0-9_]*/y);
let id = ID.map((x) => new Id(x));

let NOT = token(/!/y).map((_) => Not);
let EQUAL = token(/==/y).map((_) => Equal);
let NOT_EQUAL = token(/!=/y).map((_) => NotEqual);
let PLUS = token(/[+]/y).map((_) => Add);
let MINUS = token(/[-]/y).map((_) => Subtract);
let STAR = token(/[*]/y).map((_) => Multiply);
let SLASH = token(/[/]/y).map((_) => Divide);

let expression: Parser<AST> = Parser.error(
  "expression parser used before definition"
);
