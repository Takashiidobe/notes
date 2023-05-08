# Implement Queue using Stacks

Implement a first in first out (FIFO) queue using only two stacks. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:

    void push(int x) Pushes element x to the back of the queue.
    int pop() Removes the element from the front of the queue and returns it.
    int peek() Returns the element at the front of the queue.
    boolean empty() Returns true if the queue is empty, false otherwise.

Notes:

    You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
    Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue) as long as you use only a stack's standard operations.

Example 1:

```
Input
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 1, 1, false]
```

Explanation
```
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false
```

Constraints:

    1 <= x <= 9
    At most 100 calls will be made to push, pop, peek, and empty.
    All the calls to pop and peek are valid.

Follow-up: Can you implement the queue such that each operation is amortized O(1) time complexity? In other words, performing n operations will take overall O(n) time even if one of those operations may take longer.

## Solution

To emulate a queue with a stack, we use two stacks, pushing to one
stack, and when we need to pop the stack, we empty out the stack we push
to, and pop it into another stack.

If we only pop when the first stack is empty, and we cache the top
value, we can make most operations O(1).

```python
class MyQueue:
    def __init__(self):
        self.stack_1 = []
        self.stack_2 = []

    def push(self, x: int) -> None:
        self.stack_1.append(x)

    def pop(self) -> int:
        self.peek()
        return self.stack_2.pop()

    def peek(self) -> int:
        if not self.stack_2:
            while self.stack_1:
                popped = self.stack_1.pop()
                self.stack_2.append(popped)
        return self.stack_2[-1]

    def empty(self) -> bool:
        return not self.stack_1 and not self.stack_2
```
