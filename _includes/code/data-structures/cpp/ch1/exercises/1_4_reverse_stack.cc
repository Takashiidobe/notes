// Suppose you have a Stack, s, that supports only the
// push(x) and pop() operations. Show how, using only a
// FIFO Queue, q, you can reverse the order of all
// elements in s.

// Using a stack, we can pop all of the items and enqueue them into a queue.
// Then, we dequeue the items of a stack while pushing them into the stack
// again. the items have been reversed.
