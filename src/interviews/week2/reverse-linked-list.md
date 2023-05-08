# Reverse Linked List

Given the head of a singly linked list, reverse the list, and return the reversed list.

Example 1:

```
Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]
```

Example 2:

```
Input: head = [1,2]
Output: [2,1]
```

Example 3:

```
Input: head = []
Output: []
```

## Solution

To reverse the linked list, create a dummy node, and then while
iterating through the list, point the next node to the dummy node
(reversing it). When we hit the end, return the end node.

```python
class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        prev = None
        while head:
            temp, head.next = head.next, prev
            prev, head = head, temp
        return prev
```
