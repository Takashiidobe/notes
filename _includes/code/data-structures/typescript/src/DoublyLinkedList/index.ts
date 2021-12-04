import { DoublyLinkedListNode } from "./DoublyLinkedListNode";

export class DoublyLinkedList<T> {
  private _head: DoublyLinkedListNode<T> | null;
  private _tail: DoublyLinkedListNode<T> | null;
  private _length = 0;
  constructor(arg?: T | T[]) {
    if (arg !== undefined) {
      if (Array.isArray(arg)) {
        for (const val of arg) {
          this.push(val);
        }
      } else {
        this.push(arg);
      }
    }
  }

  isEmpty(): boolean {
    return this._length === 0;
  }

  toString(): string {
    if (this._length > 0) {
      let current = this._head;
      let str = "";
      while (current) {
        str += current.value;
        str += "->";
        current = current.next;
      }
      str = str.slice(0, -2);
      return str;
    } else {
      return "";
    }
  }

  get length() {
    return this._length;
  }

  get head() {
    return this._head;
  }

  get tail() {
    return this._tail;
  }

  *items() {
    let current = this._head;
    while (current) {
      yield current.value;
      current = current.next;
    }
  }

  [Symbol.iterator]() {
    return this.items();
  }

  contains(item: T): boolean {
    let current = this._head;
    while (current) {
      if (item === current.value) {
        return true;
      }
      current = current.next;
    }
    return false;
  }

  shift(): T | null {
    if (!this.isEmpty()) {
      const nodeVal = this._head.value;
      if (this._length === 1) {
        this._tail = null;
        this._head = null;
      } else {
        this._head = this._head.next;
        this._head.prev = null;
      }
      this._length--;
      return nodeVal;
    }
    return null;
  }

  add(item: T, pos: number) {
    if (pos <= 0) {
      this.unshift(item);
    } else if (pos >= this._length) {
      this.push(item);
    } else {
      const newNode = new DoublyLinkedListNode<T>(item);
      let current = this._head;
      let index = 0;
      while (index < pos - 1) {
        current = current.next;
        index++;
      }
      current.prev.next = newNode;
      newNode.prev = current.prev;
      current.prev = newNode;
      newNode.next = current;
      this._length++;
    }
  }

  delete(pos: number) {
    if (pos <= 0) {
      this.shift();
    } else if (pos >= this._length) {
      this.pop();
    } else if (!this.isEmpty()) {
      let current = this._head;
      let index = 0;
      while (index < pos - 1) {
        current = current.next;
        index++;
      }
      const nextNode = current.next;
      const prevNode = current.prev;
      nextNode.prev = prevNode;
      prevNode.next = nextNode;
      this._length--;
    }
  }

  unshift(item: T) {
    const newNode = new DoublyLinkedListNode<T>(item);
    if (this.isEmpty()) {
      this._head = newNode;
      this._tail = newNode;
    } else {
      newNode.next = this._head;
      this._head.prev = newNode;
      this._head = newNode;
    }
    this._length++;
  }

  push(item: T) {
    const newNode = new DoublyLinkedListNode<T>(item);
    if (this.isEmpty()) {
      this._head = newNode;
      this._tail = newNode;
    } else {
      newNode.prev = this._tail;
      this._tail.next = newNode;
      this._tail = newNode;
    }
    this._length++;
  }

  pop(): T | null {
    if (!this.isEmpty()) {
      const nodeVal = this._tail.value;
      if (this._length === 1) {
        this._head = null;
        this._tail = null;
      } else {
        this._tail = this._tail.prev;
        this._tail.next = null;
      }
      this._length--;
      return nodeVal;
    }
    return null;
  }
}
