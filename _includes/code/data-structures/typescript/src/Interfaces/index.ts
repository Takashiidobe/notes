interface LinearContainer<T> {
  iterator(): Generator<T, any, unknown>;
  next(index: number): IteratorResult<T>;
  [Symbol.iterator](): Generator<T, any, unknown>;
  at(index: number): T;
  [Symbol.toStringTag]: string;
  add(item: T, index: number): boolean;
  items: T[];
  reverse(): T[];
  contains(item: T): boolean;
  toString(): string;
  toArray(): T[];
}

interface ReverseIterableIterator<T> extends IterableIterator<T> {
  reverseIterator(): IterableIterator<T>;
}

interface CircularContainer<T> {
}

interface SinglyLinkedListNode<T> {
  value: T;
  next: SinglyLinkedListNode<T> | null;
}
