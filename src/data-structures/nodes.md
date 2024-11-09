---
title: Nodes
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Friday, November 8th 2024, 10:21:47 pm
---

# Nodes

- a Node has a value and (a) pointer(s) to another memory address or
  NULL.
- This might look something like this, for a Singly Linked List Node:

## Singly Linked List Node

```c
struct SinglyLinkedListNode {
  int value;
  struct SinglyLinkedListNode* next;
};
```

## Doubly Linked List Node

```c
struct DoublyLinkedListNode {
  int value;
  struct DoublyLinkedListNode* next;
  struct DoublyLinkedListNode* prev;
};
```

## Tree Node

- A Binary Tree Node might look like this:

```c
struct BinaryTreeNode {
  int value;
  struct BinaryTreeNode* left;
  struct BinaryTreeNode* right;
  struct BinaryTreeNode* parent; // this is optional
};
```

### Empty BinaryTreeNode

![BinaryTreeNode](/ChildlessBinaryTreeNode.png)

### Full BinaryTreeNode

![FullBinaryTreeNode](/FullBinaryTreeNode.png)
