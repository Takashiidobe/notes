---
title: "Let us count!"
pdf: "[[notes-on-discrete-mathematics.pdf]]"
---

# Let us count!

Prev: [[courses/notes-on-discrete-mathematics/01-introduction]]
Next: [[03-induction]]

**2.1** How many ways can these people be seated at the table, if Alice too can sit any- where?

--- 

There are seven guests at a birthday party.

How many different ways can they shake hands (with two people)? The answer is 21, because there are $7 * 6$ ways to make pairs of two, and then divide by two to count only the unique handshakes.

---

**2.2** What is the number of "matchings" in Carl’s sense (when it matters who sits on which side of the board, but the boards are all alike), and in Diane’s sense (when it is the other way around)?

---

**2.3** Name sets whose elements are  
(a) buildings,  
(b) people,  
(c) students,  
(d) trees,  
(e) numbers,  
(f) points.  

---

**2.4** What are the elements of the following sets:  
(a) army,  
(b) mankind,  
(c) library,  
(d) the animal kingdom?  
(e) the cardinalities of $\mathbb{Z}$ and $\mathbb{R}$. 
This is the subject matter of set theory and does not concern us here.  

---

**2.5** Name sets having cardinality  
(a) 52,  
(b) 13,  
(c) 32,  
(d) 100,  
(e) 90,  
(f) 2,000,000.  

---

**2.6** What are the elements of the following (admittedly peculiar) set:  

$$
\{\text{Alice}, \{1\}\}?
$$

---

**2.7** We have not written up all subset relations between various sets of numbers; for example, $ \mathbb{Z} \subseteq \mathbb{R} $ is also true. How many such relations can you find between the sets  

$$
\varnothing,\ \mathbb{N},\ \mathbb{Z}^+,\ \mathbb{Z},\ \mathbb{Q},\ \mathbb{R}?
$$

---

**2.8** Is an “element of a set” a special case of a “subset of a set”?  

---

**2.9** List all subsets of $\{0, 1, 3\}$. How many do you get?  

---

**2.10** Define at least three sets, of which $\{\text{Alice}, \text{Diane}, \text{Eve}\}$ is a subset.  

---

**2.11** List all subsets of $\{a, b, c, d, e\}$, containing $a$ but not containing $b$.  

---

**2.12** Define a set, of which both $\{1,3,4\}$ and $\{0,3,5\}$ are subsets. Find such a set with a smallest possible number of elements.  

---

**2.13**  
(a) Which set would you call the union of $\{a, b, c\}$, $\{a, b, d\}$ and $\{b, c, d, e\}$?  

(b) Find the union of the first two sets, and then the union of this with the third. Also, find the union of the last two sets, and then the union of this with the first set. Try to formulate what you observed.  

(c) Give a definition of the union of more than two sets.  

---

**2.14** Explain the connection between the notion of the union of sets and exercise 2.2.  

---

**2.15** We form the union of a set with 5 elements and a set with 9 elements. Which of the following numbers can we get as the cardinality of the union:  

$$
4,\ 6,\ 9,\ 10,\ 14,\ 20?
$$

---

**2.16** We form the union of two sets. We know that one of them has $n$ elements and the other has $m$ elements. What can we infer for the cardinality of the union?  

---

**2.17** What is the intersection of  
(a) the sets $\{0, 1, 3\}$ and $\{1, 2, 3\}$;  
(b) the set of girls in this class and the set of boys in this class;  
(c) the set of prime numbers and the set of even numbers?  

---

**2.18** We form the intersection of two sets. We know that one of them has $n$ elements and the other has $m$ elements. What can we infer for the cardinality of the intersection?  

---

**2.19** Prove that  

$$
|A \cup B| + |A \cap B| = |A| + |B|.
$$

---

**2.20** The **symmetric difference** of two sets $A$ and $B$ is the set of elements that belong to exactly one of $A$ and $B$.  

(a) What is the symmetric difference of the set $\mathbb{Z}^+$ of non-negative integers and the set $E$ of even integers  

$$
E = \{\ldots, -4, -2, 0, 2, 4, \ldots\}
$$

(contains both negative and positive even integers)?  

(b) Form the symmetric difference of $A$ and $B$, to get a set $C$. Form the symmetric difference of $A$ and $C$. What did you get? Give a proof of the answer.

---
**2.21** Under the correspondence between numbers and subsets described above, which number corresponds to subsets with 1 element?

---
 **2.22** What is the number of subsets of a set with $n$ elements that contain a given element?

---
 **2.23** What is the number of integers with (a) at most $n$ decimal digits; (b) exactly $n$ digits?

---
 **2.24** How many bits (binary digits) does $2^{100}$ have when written in base $2$?

---
 **2.25** Find a formula for the number of digits of $2^n$.
 
---

**2.26** Draw a tree illustrating the way we counted the number of strings of length 2 formed from the characters a, b and c, and explain how it gives the answer. Do the same for the more general problem when $n = 3$, $k_1 = 2$, $k_2 = 3$, $k_3 = 2$.

  ---

  **2.27** In a sport shop, there are T-shirts of 5 different colors, shorts of 4 different colors, and socks of 3
  different colors. How many different uniforms can you compose from these items?

  ---

  **2.28** On a ticket for a soccer sweepstake, you have to guess 1, 2, or X for each of 13 games. How many different ways can you fill out the ticket?

  ---

  **2.29** We roll a dice twice; how many different outcomes can we have (a 1 followed by a 4 is different from a 4
  followed by a 1)?

  ---

  **2.30** We have 20 different presents that we want to distribute to 12 children. It is not required that every
  child gets something; it could even happen that we give all the presents to the same child. In how many ways can
  we distribute the presents?

  ---

  **2.31** We have 20 kinds of presents; this time, we have a large supply from each. We want to give presents to 12
  children. Again, it is not required that every child gets something; but no child can get two copies of the same
  present. In how many ways can we give presents?

---

**2.32** $n$ boys and $n$ girls go out to dance. In how many ways can they all dance simultaneously? (We assume that only couples of different sex dance with each other.)

  ---

  **2.33** (a) Draw a tree for Alice’s solution of enumerating the number of ways 6 people can play chess, and
  explain Alice’s argument using the tree.
  (b) Solve the problem for 8 people. Can you give a general formula for $2n$ people?

  ---

  **2.34** (a) Which is larger, $n$ or $n(n - 1)/2$?
  (b) Which is larger, $n^2$ or $2^n$?

  ---

  **2.35** (a) Prove that $2^n > n^3$ if $n$ is large enough.
  (b) Use (a) to prove that $2^n/n^2$ becomes arbitrarily large if $n$ is large enough.


Prev: [[courses/notes-on-discrete-mathematics/01-introduction]]
Next: [[03-induction]]
