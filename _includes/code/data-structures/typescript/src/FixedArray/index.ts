class FixedArray<T> implements LinearContainer<T> {
  private _items: T[];
  constructor(readonly _length: number = 8) {
    this._items = new Array(_length);
  }

  get [Symbol.toStringTag](): string {
    return "FixedArray";
  }

  *iterator(): Generator<T, any, unknown> {
    let index = 0;
    while (index < this._length) {
      yield this._items[index];
      index++;
    }
  }

  *reverseIterator(): Generator<T, any, unknown> {
    let index = this._length - 1;
    while (index >= 0) {
      yield this._items[index];
      index--;
    }
  }

  public next(index: number): IteratorResult<T> {
    if (index < this._length - 1) {
      return {
        done: false,
        value: this._items[index + 1],
      };
    } else {
      return {
        done: true,
        value: undefined,
      };
    }
  }

  [Symbol.iterator](): Generator<T, any, unknown> {
    return this.iterator();
  }

  at(index: number): T {
    return this._items[index];
  }

  contains(item: T): boolean {
    return this._items.includes(item);
  }

  clear() {
    this._items = new Array(this._length);
  }

  add(item: T, index: number): boolean {
    if (index >= 0 && index < this._length) {
      this._items[index] = item;
      return true;
    }
    return false;
  }

  get items(): T[] {
    return this.toArray();
  }

  reverse(): T[] {
    return this._items = this._items.reverse();
  }

  toString(): string {
    return this._items.toString();
  }

  toArray(): T[] {
    return this._items;
  }
}

let arr = new FixedArray<number>(10);

for (let i = 0; i < 10; i++) {
  arr.add((i + 1) * 10, i);
}

for (let i of arr) {
  console.log(i);
}

console.log(arr.next(0));

console.log(arr.items);
console.log(arr.at(0));
console.log(arr.toString());
