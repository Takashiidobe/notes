---
title: "A Skip List Cookbook"
pdf_url: "[[a-skip-list-cookbook.pdf]]"
---
This paper gives use cases for Skip Lists, which can match or outperform balanced trees in versatility and performance and be simpler to implement.

## Skip Lists tl;dr

- Skip lists are probabilistically balanced linked lists build from multiple levels of forward pointers.
- Each node gets a random level. Higher nodes are sparser lanes to speed up search.
- Basic ops, search, insert, delete run in $O(\log{n})$ time. This is similar to balanced trees but with smaller constant factors + less pointer manipulation.

## Recipes

**Search Fingers** for locality-aware search
- A search finger remembers the search path of the last operation.
- Searching for an element at distance $k$ from the previous item can be done in $O(\log{k})$ time.

**Optimal Merging** of skip lists
- Merging two skip lists can be done by taking a block of elements from one list, splicing that block into the output list in $O(\log{k})$ time, where $k$ is the block size.
- Over the entire merge, the cost is this where $S_i$ and $T_i$ are the block sizes per list:
$$
O(j + \sum{\log{S_i}} + k + \sum{\log{T_i}})
$$
- In the case of pure concatenation, the merge runs in $O(\log{n})$ time. This is better than merging two trees, which is in $O(m + \log{n})$ time.

**Splitting** and **Concatenating**
- Splitting a list at a key $k$:
$$x \in
\begin{cases}
L_{\text{left}}, & x < k \\
L_{\text{right}}, & x \ge k
\end{cases}$$

- Or concatenating two lists where all keys are less than keys of the second:
$$C[i] =
\begin{cases}
L_1[i], & 1 \le i \le |L_1| \\
L_2[i - |L_1|], & |L_1| < i \le |L_1| + |L_2|
\end{cases}$$


**Linear** time list/rank
- We can treat skip lists as a sequence as well that supports list/rank operations:
- Return the element at position $k$.
- Insert after position $k$.
- Delete at position $k$.
- Given a key $k$, what is its rank in the list?

1. Each forward pointer is augmented with a distance: `*distance` which tells us how many bottom-level nodes you skip when you follow the `forward` pointer.
2. Then to search by position, we follow `forward`, incrementing our current position, as long as we don't overshoot the position we want to search for. If we do overshoot, drop down one-level and try again. We continue until we cannot overshoot, the node after the current one is the node at rank $k$. Thus, rank can be found in $O(\log{n})$.

Insertion, deletion, and updates can be built over this idea. All of those will have to update both the forward pointer and the distance pointer.

## Refinements

There are tweaks that can be done to skiplists that make it better for certain cases.

**Fewer key** comparisons:
- For expensive comparisons, the algorithms can be tweaked to avoid comparing against the same node's key twice along a search path.

**Duplicate keys**:
- To allow duplicates, insert always adds a new node, search/delete affect only the most recently inserted.

**Alternative Level distributions**:
- You can tune memory usage + search cost + variance by using two parameters, $p$ which is normally $\frac{1}{2}$, and a shift parameter, $k$, which is roughly how many levels you throw away at the bottom, scaling down average height for more space savings at the cost of worse search time.