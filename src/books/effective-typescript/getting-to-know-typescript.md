---
title: getting-to-know-typescript
---

to Know Typescript"

# Getting to Know Typescript

Next:
[typescripts-type-system](typescripts-type-system.md)

1.  Understand the Relationship Between Typescript and Javascript

Typescript is a superset of Javascript, with extra functionality:

We can annotate the type of a function like so:

```ts
function greet(who: string) {
  console.log("Hello", who);
}
```

Typescript has better error handling than javascript:

```js
let city = "new york city";
console.log(city.toUppercase());
```

Will throw this error:

    TypeError: city.toUppercase is not a function

Typescript's type checker can spot the problem a little bit better:

```ts
let city = "new york city";
console.log(city.toUppercase());
// ~~~~~~~~~~~ Property 'toUppercase' does not exist on type
//             'string'. Did you mean 'toUpperCase'?
```

Next:
[typescripts-type-system](typescripts-type-system.md)
