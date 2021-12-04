---
title: check-if-array-in-js
---

If Array In Js

# Check if Array in JS

The `Array` class has a function on it called
[`isArray()`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/isArray.md)
which can be used to check if something is an array.

```js
> Array.isArray('Hello, World!');
// => false

> Array.isArray(['One', 2, [3]]);
// => true

> Array.isArray({ foo: 'bar' });
// => false

> Array.isArray([]);
// => true
```

The MDN docs provide an [example
polyfill](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/isArray#Polyfill.md)
if it is not natively available.

```js
if (!Array.isArray) {
  Array.isArray = function (arg) {
    return Object.prototype.toString.call(arg) === "[object Array]";
  };
}
```
