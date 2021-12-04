---
title: introduction
---

# The Little Book of Semaphores

Next: [semaphores](semaphores.md)

## 1.1 Synchronization

### Serialization

- _A_ happens before _B_

### Mutual Exclusion

- _A_ and _B_ cannot happen at the same time.

### 1.2 Execution Model

- In a serial computer, instructions execute one after another in
  order. Some computers are parallel, which means they may not execute
  sequentially.

#### Puzzle:

- You eat lunch at 11:59 and Bob eats lunch at 12:01. Who ate lunch
  first? - You don't know who ate lunch first, because your clocks
  could be wrong.

- How can you guarantee that you will eat lunch before Bob tomorrow? -
  Tell him not to eat lunch until after you've called him. - Eat
  lunch, and then call Bob. - This risks starvation (Bob can't eat
  until you call him, which you can sacrifice correctness for (tell
  him to eat at 12:30 his time anyway so he goes eventually)).

### 1.3 Serialization with messages

- Concurrency is defined as: - two events are **concurrent** if we
  cannot tell by looking at the program which will happen first.

### 1.4 Non-determinism

- Some programs are **non-deterministic**, which means it is not
  possible to tell by looking at the program what happens when it
  executes.

Thread A Thread B

---

print('yes') print('no')

- In this program, we don't know if it prints "yes" then "no" or
  "no" then "yes".

### 1.5 Shared Variables

- Most of the time variables in threads are **local**, meaning they
  are private to the thread. Some are **shared**, which means they can
  be read by more than one thread.

#### 1.5.1 Concurrent writes

Thread A Thread B

---

x = 5 x = 7
print(x)

- Puzzle: What path yields output 5 and final value 5? - Thread A runs
  first
- Puzzle: What path yields output 7 and final value 7? - Thread B runs
  first
- Puzzle: Is there a path that yields output 7 and final value 5? Can
  you prove it? - If Thread B runs first, and the print(x) call runs
  before x = 5 (which it shouldn't), then this could work.

#### 1.5.2 Concurrent updates

- an update reads the value of a variable and writes to that new value
  with that value.

Thread A Thread B

---

count += 1 count += 1

- This can result in either one increment or two increments.

Next: [semaphores](semaphores.md)
