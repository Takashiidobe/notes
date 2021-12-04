// class SinglyLinkedList<T> implements LinearContainer<T> {
//   private _head: SinglyLinkedListNode<T>;
//   private _tail: SinglyLinkedListNode<T>;
//   private _length: number = 0;
//   constructor() {}

//   *iterator(): Generator<T, any, unknown> {
//     let copy = this._head;
//     while (copy) {
//       copy = copy.next;
//     }
//   }

//   *reverseIterator(): Generator<T, any, unknown> {
//     let index = this._length - 1;
//     while (index >= 0) {
//       yield this._items[index];
//       index--;
//     }
//   }
// }

// class SinglyLinkedListNode<T> implements SinglyLinkedListNode<T> {
//   private _next: SinglyLinkedListNode<T>;
//   constructor(private _value: T) {}

//   get next(): SinglyLinkedListNode<T> | null {
//     return this._next;
//   }

//   set next(val: SinglyLinkedListNode<T>) {
//     this._next = val;
//   }

//   get value(): T {
//     return this._value;
//   }

//   set value(val: T) {
//     this._value = val;
//   }
// }
