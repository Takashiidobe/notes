export class Pair<S, T> {
  constructor(public _first: S = null, public _second: T = null) {}

  get first() {
    return this._first;
  }

  get second() {
    return this._second;
  }

  set first(val: S) {
    this.first = val;
  }

  set second(val: T) {
    this.second = val;
  }

  toString() {
    return `(${this.first.toString()}, ${this.second.toString()})`;
  }

  equals(other: Pair<S, T>) {
    return this.toString() === other.toString();
  }
}

console.log(new Pair([5], [5]).equals(new Pair([5], [5])));
