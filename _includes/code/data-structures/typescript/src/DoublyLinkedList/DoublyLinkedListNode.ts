export interface _DoublyLinkedListNode<T> {
  value: T;
  next: DoublyLinkedListNode<T> | null;
  prev: DoublyLinkedListNode<T> | null;
}

export class DoublyLinkedListNode<T> implements _DoublyLinkedListNode<T> {
  constructor(
    private _value: T,
    private _next: DoublyLinkedListNode<T> | null = null,
    private _prev: DoublyLinkedListNode<T> | null = null,
  ) {}

  get next(): DoublyLinkedListNode<T> | null {
    return this._next;
  }

  set next(val: DoublyLinkedListNode<T>) {
    this._next = val;
  }

  get prev(): DoublyLinkedListNode<T> | null {
    return this._prev;
  }

  set prev(val: DoublyLinkedListNode<T>) {
    this._prev = val;
  }

  get value(): T {
    return this._value;
  }

  set value(val: T) {
    this._value = val;
  }
}
