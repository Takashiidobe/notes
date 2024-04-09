# Print Vertically

Given a string s. Return all the words vertically in the same order in which they appear in s.
Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
Each word would be put on only one column and that in one column there will be only one word.

Example 1:

Input: s = "HOW ARE YOU"
Output: ["HAY","ORO","WEU"]
Explanation: Each word is printed vertically. 
 "HAY"
 "ORO"
 "WEU"

Example 2:

Input: s = "TO BE OR NOT TO BE"
Output: ["TBONTB","OEROOE","   T"]
Explanation: Trailing spaces is not allowed. 
"TBONTB"
"OEROOE"
"   T"

Example 3:

Input: s = "CONTEST IS COMING"
Output: ["CIC","OSO","N M","T I","E N","S G","T"]

## Approach

We want to traverse the string in the opposite way, instead of word by
word, letter by letter per word.

First, we collect the words into an array:

```python
words = s.split(' ')
```

Next, we need the longest word, because if the current word is shorter
than the current index we iterate on, we want to print a space
character.

```python
longest_word = max(len(w) for w in words)
```

Finally, we loop through, going from 0..longest_word (the index of each
word) and from each word we create the current string.

```python
res = []
for i in range(longest_word):
    curr = []
    for word in words:
        if i >= len(word):
            curr.append(' ')
        else:
            curr.append(word[i])
    res.append(''.join(curr).rstrip())
```

We strip the right hand side of the string since we don't want trailing
spaces.
