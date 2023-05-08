# Evaluate Reverse Polish Notation

Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are `+`, `-`, `*`, and `/`. Each operand may be an integer or another expression.

Note that division between two integers should truncate toward zero.

It is guaranteed that the given RPN expression is always valid. That means the expression would always evaluate to a result, and there will not be any division by zero operation.

Example 1:

```
Input: tokens = ["2","1","+","3","*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
```

Example 2:

```
Input: tokens = ["4","13","5","/","+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
```

Example 3:

```
Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
```

## Solution

Reverse RPN can be solved by using a stack. Evaluate each operator as
soon as it comes onto the stack, by popping two numbers off the stack.
The tricky part here is the question asks for fixed-width integer
division, which in python requires `int(left / right)`.

```python
class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        nums = []

        for token in tokens:
            if token in ["*", "/", "+", "-"]:
                right = nums.pop()
                left = nums.pop()
                if token == "*":
                    nums.append(left * right)
                elif token == "/":
                    nums.append(int(left / right))
                elif token == "-":
                    nums.append(left - right)
                elif token == "+":
                    nums.append(left + right)
            else:
                nums.append(int(token))

        return nums[-1]
```
