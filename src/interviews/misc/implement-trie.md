# Implement Trie

A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:

- Trie() Initializes the trie object.
- void insert(String word) Inserts the string word into the trie.
- boolean search(String word) Returns true if the string word is in the trie (i.e., was inserted before), and false otherwise.
- boolean startsWith(String prefix) Returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise.

Example 1:

Input
```js
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
Output
[null, null, true, false, true, null, true]
```

Explanation
```
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // return True
trie.search("app");     // return False
trie.startsWith("app"); // return True
trie.insert("app");
trie.search("app");     // return True
```

## Solution

```python
class TrieNode:
    def __init__(self):
        self.is_word = False
        self.children = defaultdict(TrieNode)

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        curr_node = self.root

        for char in word:
            curr_node = curr_node.children[char]

        curr_node.is_word = True

    def search(self, word: str) -> bool:
        curr_node = self.root

        for char in word:
            if char not in curr_node.children:
                return False
            curr_node = curr_node.children[char]

        return curr_node.is_word

    def startsWith(self, prefix: str) -> bool:
        curr_node = self.root

        for char in prefix:
            if char not in curr_node.children:
                return False
            curr_node = curr_node.children[char]

        return True
```
