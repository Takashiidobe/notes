# Answers to exercises

## 2 Let us count!

---

**2.1 A party**

2.1. $7!$.

2.1. Carl: $15 \cdot 2^3 = 120$. Diane: $15 \cdot 3! = 90$.

---

**2.2 Sets**

2.2. (a) all houses in a street; (b) an Olympic team; (c) class of ’99; (d) all trees in a forest; (e) the set of rational numbers; (f) a circle in the plane.

2.2. (a) soldiers; (b) people; (c) books; (d) animals.

2.2. (a) all cards in a deck; (b) all spades in a deck; (c) a deck of Swiss cards; (d) non-negative integers with at most two digits; (e) non-negative integers with exactly two digits; (f) inhabitants of Budapest, Hungary.

2.2. Alice, and the set whose only element is the number $1$.

2.2. $6 \cdot \frac{5}{2} = 15$.

2.2. No.

2.2. $\emptyset$, $\{0\}$, $\{1\}$, $\{3\}$, $\{0,1\}$, $\{0,3\}$, $\{1,3\}$, $\{0,1,3\}$. $8$ subsets.

2.2. women; people at the party; students of Yale.

2.2. $\mathbb{Z}$ or $\mathbb{Z}^+$. The smallest is $\{0,1,3,4,5\}$.

2.2. (a) $\{a,b,c,d,e\}$. (b) The union operation is associative. (c) The union of any set of sets consists of those elements which are elements of at least one of the sets.

2.2. The union of a set of sets $\{A_1,A_2,\dots,A_k\}$ is the smallest set containing each $A_i$ as a subset.

2.2. $6, 9, 10, 14$.

2.2. The cardinality of the union is at least the larger of $n$ and $m$ and at most $n + m$.

2.2. (a) $\{1,3\}$; (b) $\emptyset$; (c) $\{2\}$.

2.2. The cardinality of the intersection is at most the minimum of $n$ and $m$.

2.2. The common elements of $A$ and $B$ are counted twice on both sides; the elements in either $A$ or $B$ but not both are counted once on both sides.

2.2. (a) The set of negative even integers and positive odd integers. (b) $B$.

---

**2.3 The number of subsets**

2.3. Powers of $2$.

2.3. $2^{\,n-1}$.

2.3. (a) $2 \cdot 10^n - 1$; (b) $2 \cdot (10^n - 10^{n-1})$.

2.3. $1 + \lfloor n \lg 2 \rfloor$.

---

**2.4 Sequences**

2.4. The trees have $9$ and $8$ leaves, respectively.

2.4. $5 \cdot 4 \cdot 3 = 60$.

2.4. $3^{13}$.

2.4. $6 \cdot 6 = 36$.

2.4. $12^{20}$.

2.4. $(2^{20})^{12}$.

---

**2.5 Permutations**

2.5. $n!$.

2.5. (b) $7 \cdot 5 \cdot 3 = 105$. In general, $(2n - 1)(2n - 3) \cdots 3 \cdot 1$.

2.5. (a) $\dfrac{n(n - 1)}{2}$ is larger for $n \ge 4$. (b) $2^n$ is larger for $n \ge 5$.

2.5. (a) This is true for $n \ge 10$. (b) $\dfrac{2^n}{n^2} > n$ for $n \ge 10$.

## 3 Induction

---

**3.1 The sum of odd numbers**

3.1. One of $n$ and $n + 1$ is even, so the product $n(n + 1)$ is even. By induction: true for $n = 1$; if $n > 1$ then
$$
n(n + 1) = (n - 1)n + 2n,
$$
and $(n - 1)n$ is even by the induction hypothesis, $2n$ is even, and the sum of two even numbers is even.

3.1. True for $n = 1$. If $n > 1$ then
$$
1 + 2 + \cdots + n = (1 + 2 + \cdots + (n - 1)) + n = \frac{(n - 1)n}{2} + n = \frac{n(n + 1)}{2}.
$$

3.1. The youngest person will count $n - 1$ handshakes. The $7$-th oldest will count $6$ handshakes. So they count
$$
1 + 2 + \cdots + (n - 1)
$$
handshakes. We also know that there are $\dfrac{n(n - 1)}{2}$ handshakes.

3.1. Compute the area of the rectangle in two different ways.

3.1. By induction on $n$, true for $n = 1$. For $n > 1$, we have
$$
1 \cdot 2 + 2 \cdot 3 + 3 \cdot 4 + \cdots + (n - 1)n
= \frac{(n - 2)(n - 1)n}{3} + (n - 1)n
= \frac{(n - 1)n(n + 1)}{3}.
$$

3.1. If $n$ is even, then
$$
1 + n = 2 + (n - 1) = \cdots = \left(\frac{n}{2} - 1\right) + \frac{n}{2} = n + 1,
$$
so the sum is
$$
\frac{n}{2}(n + 1) = \frac{n(n + 1)}{2}.
$$
If $n$ is odd then we have to add the middle term separately.

3.1. If $n$ is even, then
$$
1 + (2n - 1) = 3 + (2n - 3) = \cdots = (n - 1) + (n + 1) = 2n,
$$
so the sum is
$$
\frac{n}{2}(2n) = n^2.
$$
Again, if $n$ is odd the solution is similar, but we have to add the middle term separately.

3.1. By induction. True for $n = 1$. If $n > 1$ then
$$
1^2 + 2^2 + \cdots + (n - 1)^2 = (1^2 + 2^2 + \cdots + (n - 1)^2) + n^2
= \frac{(n - 1)n(2n - 1)}{6} + n^2
= \frac{n(n + 1)(2n + 1)}{6}.
$$

3.1. By induction. True for $n = 1$. If $n > 1$ then
$$
2^0 + 2^1 + 2^2 + \cdots + 2^{n-1}
= (2^0 + 2^1 + \cdots + 2^{n-2}) + 2^{n-1}
= (2^{n-1} - 1) + 2^{n-1}
= 2^n - 1.
$$

---

**3.2 Subset counting revisited**

3.2. *(Strings)* True for $n = 1$. If $n > 1$ then to get a string of length $n$ we can start with a string of length $n - 1$ (this can be chosen in $k^{n-1}$ ways by the induction hypothesis) and append an element (this can be chosen in $k$ ways). So we get $k^{n-1} \cdot k = k^n$.

*(Permutations)* True for $n = 1$. To seat $n$ people, we can start with seating the oldest (this can be done in $n$ ways) and then seating the rest (this can be done in $(n - 1)!$ ways by the induction hypothesis). We get $n \cdot (n - 1)! = n!$.

3.2. True if $n = 1$. Let $n > 1$. The number of handshakes between $n$ people is the number of handshakes by the oldest person ($n - 1$) plus the number of handshakes between the remaining $n - 1$ (which is $\dfrac{(n - 1)(n - 2)}{2}$ by the induction hypothesis). We get
$$
(n - 1) + \frac{(n - 1)(n - 2)}{2} = \frac{n(n - 1)}{2}.
$$

13.1. By induction. True if $n = 1$. Let $n > 1$. Assume the description of the coloring is valid for the first $n - 1$ circles. If we add the $n$-th, the color and the parity do not change outside this circle; both change inside the circle. So the description remains valid.

13.1. (a) By induction. True for $1$ line. Adding a line, we recolor all regions on one side. (b) One possible description: designate a direction as “up”. Let $P$ be any point not on any of the lines. Start a semiline “up” from $P$. Count how many of the given lines intersect it. Color according to the parity of this intersection number.

3.2. We did not check the base case $n = 1$.

3.2. The proof uses that there are at least four lines. But we only checked $n = 1, 2$ as base cases. The assertion is false for $n = 3$ and also for every value after that.

---

**3.3 Counting regions**

3.3. True for $n = 1$. Let $n > 1$. Delete any line. The remaining lines divide the plane into
$$
\frac{(n - 1)n}{2} + 1
$$
regions by the induction hypothesis. The last line cuts $n$ of these into two. So we get
$$
\frac{(n - 1)n}{2} + 1 + n = \frac{n(n + 1)}{2} + 1.
$$

---

# 4 Counting subsets

---

**4.1 The number of ordered subsets**

4.1. (I don’t think you could really draw the whole tree; it has almost $10^{20}$ leaves. It has $11$ levels of nodes.)

4.1. (a) $100!$. (b) $90!$. (c) $\dfrac{100!}{90!} = 100 \cdot 99 \cdot \dots \cdot 91$.

4.1. $\dfrac{n!}{(n-k)!} = n(n - 1) \cdot \dots \cdot (n - k + 1)$.

4.1. In one case, repetition is not allowed, while in the other case, it is allowed.

---

**4.2 The number of subsets of a given size**

4.2. Handshakes; lottery; hands in bridge.

4.2. See next chapter.

4.2. $\dfrac{n(n - 1)}{2} + \dfrac{(n + 1)n}{2} = n^2$.

4.2. Solution of (b) ((a) is a special case). The identity is
$$
\binom{n}{k} = \binom{n - 1}{k} + \binom{n - 1}{k - 1}.
$$
The right-hand side counts $k$-subsets of an $n$-element set by separately counting those that do not contain a given element and those that do.

4.2. The number of $k$-element subsets is the same as the number of $(n - k)$-element subsets, since the complement of a $k$-subset is an $(n - k)$-subset and vice versa.

4.2. Both sides count all subsets of an $n$-element set.

4.2. Both sides count the number of ways to divide an $a$-element set into three sets with $a - b$, $b - c$, and $c$ elements.

---

**4.3 The Binomial Theorem**

4.3.
$$
\begin{aligned}
(x + y)^n &= (x + y)^{n-1}(x + y) \\
&= \Bigl(x^{n-1} + \binom{n-1}{1} x^{n-2}y + \dots
+ \binom{n-1}{n-2} x y^{n-2}
+ \binom{n-1}{n-1} y^{n-1}\Bigr)(x + y) \\
&= x^{n-1}(x + y)
+ \binom{n-1}{1} x^{n-2}y(x + y)
+ \dots
+ \binom{n-1}{n-2} x y^{n-2}(x + y)
+ \binom{n-1}{n-1} y^{n-1}(x + y) \\
&= (x^n + x^{n-1}y)
+ \binom{n-1}{1}(x^{n-1}y + x^{n-2}y^2)
+ \dots \\
&\quad
+ \binom{n-1}{n-2}(x^2 y^{n-2} + x y^{n-1})
+ \binom{n-1}{n-1}(x y^{n-1} + y^n) \\
&= x^n
+ \Bigl(1 + \binom{n-1}{1}\Bigr) x^{n-1}y
+ \dots
+ \Bigl(\binom{n-1}{n-2} + \binom{n-1}{n-1}\Bigr) x y^{n-1}
+ y^n \\
&= x^n
+ \binom{n}{1} x^{n-1}y
+ \binom{n}{2} x^{n-2}y^2
+ \dots
+ \binom{n}{n-1} x y^{n-1}
+ y^n.
\end{aligned}
$$

4.3. (a) $(1 - 1)^n = 0$. (b) By $\binom{n}{k} = \binom{n}{n-k}$.

4.3. Both sides count all subsets of an $n$-element set.

---

**4.4 Distributing presents**

4.4.
$$
\binom{n}{n_1}
\binom{n - n_1}{n_2}
\cdots
\binom{n - n_1 - \dots - n_{k-2}}{n_{k-1}}
=
\frac{n!}{n_1!(n - n_1)!}
\cdot
\frac{(n - n_1)!}{n_2!(n - n_1 - n_2)!}
\cdots
=
\frac{n!}{n_1! n_2! \dots n_k!},
$$
since $n - n_1 - \dots - n_{k-1} = n_k$.

4.4. (a) $n!$ (distribute positions instead of presents).  
(b) $n(n - 1) \dots (n - k + 1)$ (distribute as “presents” the first $k$ positions at the competition and $n - k$ participation certificates).  
(c) $\binom{n}{n_1}$.  
(d) Chess seating in Diane’s sense (distribute players to boards).

4.4. (a) $[n = 8]$ $8!$.  
(b) $8! \cdot \binom{8}{4}$.  
(c) $(8!)^2$.

---

**4.5 Anagrams**

4.5. $\dfrac{13!}{2^3}$.

4.5. COMBINATORICS.

4.5. Most: any word with $13$ different letters; least: any word with $13$ identical letters.

4.5. (a) $26^6$.

(b) $\binom{26}{4}$ ways to select the four letters that occur; for each selection, $\binom{4}{2}$ ways to select the two letters that occur twice; for each selection, we distribute $6$ positions to these letters ($2$ of them get $2$ positions), this gives $\dfrac{6!}{2!2!}$ ways. Thus we get
$$
\binom{26}{4} \binom{4}{2} \frac{6!}{2!2!}.
$$
(There are many other ways to arrive at the same number!)

(c) Number of ways to partition $6$ into the sum of positive integers:
$$
\begin{aligned}
6 &= 6 = 5 + 1 = 4 + 2 = 4 + 1 + 1 = 3 + 3 = 3 + 2 + 1 \\
  &= 3 + 1 + 1 + 1 = 2 + 2 + 2 = 2 + 2 + 1 + 1 \\
  &= 2 + 1 + 1 + 1 + 1 = 1 + 1 + 1 + 1 + 1 + 1,
\end{aligned}
$$
which makes $11$ possibilities.

(d) This is too difficult in this form. What was meant is the following: how many words of length $n$ are there such that none is an anagram of another? This means distributing $n$ pennies to $26$ children, and so the answer is
$$
\binom{n + 25}{26}.
$$

---

**4.6 Distributing money**

4.6. $\binom{n - k - 1}{k - 1}$.

4.6. $\binom{n + k - 1}{\ell + k - 1}$.

4.6. $\binom{kp + k - 1}{k - 1}$.
---
# 5 Pascal’s Triangle

---

**5. Basic identities**

5. This is the same as
$$
\binom{n}{k} = \binom{n}{n-k}.
$$

6. $$
\binom{n}{0} = \binom{n}{n} = 1
$$
(e.g. by the general formula for the binomial coefficients).

---

**5.1 Identities in the Pascal Triangle**

5.1.
$$
\begin{aligned}
1 +
\binom{n}{1} +
\binom{n}{2} +
\dots +
\binom{n}{n-1} +
\binom{n}{n}
&= 1 +
\Bigl(\binom{n-1}{0} + \binom{n-1}{1}\Bigr) +
\Bigl(\binom{n-1}{1} + \binom{n-1}{2}\Bigr) \\
&\quad + \dots +
\Bigl(\binom{n-1}{n-2} + \binom{n-1}{n-1}\Bigr) + 1 \\
&= 2\Bigl(\binom{n-1}{0} + \binom{n-1}{1} + \dots +
\binom{n-1}{n-2} + \binom{n-1}{n-1}\Bigr) \\
&= 2 \cdot 2^{n-1} = 2^n.
\end{aligned}
$$

5.1. The coefficient of $x^n y^n$ in
$$
\Bigl(
\binom{n}{0} x^n
+
\binom{n}{1}(x^{n-1}y + x^{n-2}y^2) + \dots +
\binom{n}{n-1} x y^{n-1}
+
\binom{n}{n} y^n
\Bigr)^2
$$
is
$$
\binom{n}{0}\binom{n}{n}
+ \binom{n}{1}\binom{n}{n-1}
+ \dots +
\binom{n}{n-1}\binom{n}{1}
+ \binom{n}{n}\binom{n}{0}.
$$

5.1. The left-hand side counts all $k$-element subsets of an $(n + m)$-element set by distinguishing them according to how many elements they pick from the first $n$.

5.1. If the largest element is $j$, the rest can be chosen in $\binom{j-1}{k}$ ways.

---

**5.2 A bird’s eye view at the Pascal Triangle**

5.2. $n = 3k + 2$.

5.2.
$$
k = \left\lfloor \frac{n - \sqrt{2n}}{2} \right\rfloor.
$$
(This is not easy: one looks at the difference of differences
$$
\Bigl(\binom{n}{k+1} - \binom{n}{k}\Bigr)
-
\Bigl(\binom{n}{k} - \binom{n}{k-1}\Bigr),
$$
and determines the value of $k$ where it turns negative.)

5.2. (a) $2^n$ is a sum with positive terms in which $\binom{n}{4}$ is only one of the terms.

(b) Assume that $n > 200$. Then
$$
\frac{2^n}{n^3}
\;\ge\;
\frac{\binom{n}{4}}{n^3}
=
\frac{n(n-1)(n-2)(n-3)}{24n^3}
>
\frac{(n/2)^3}{24n^3}
= \frac{n}{192} > 1.
$$

5.2.
$$
\binom{n}{n/2}
= \frac{n!}{\bigl((n/2)!\bigr)^2}
\sim
\frac{\left(\dfrac{n}{e}\right)^n \sqrt{2\pi n}}{
\left(\dfrac{n}{2e}\right)^n \bigl(\sqrt{\pi n}\bigr)^2}
= \frac{\left(\dfrac{n}{e}\right)^n \sqrt{2\pi n}}{
\left(\dfrac{n}{2e}\right)^n \pi n}
= 2^n \frac{\sqrt{2}}{\sqrt{\pi n}}.
$$

5.2. Using
$$
\frac{\binom{2m}{m}}{\binom{2m}{m - t}} > \frac{t^2}{m},
$$
it is enough to find a $t > 0$ for which $t^2/m \ge 1/c$. Solving for $t$, we get that
$$
t = \left\lceil \sqrt{\frac{m}{c}} \right\rceil
$$
is a good choice.

5. (a) See (c).

(b) We prove by induction on $s$ that for $0 \le s \le m - t$,
$$
\frac{\binom{2m}{m - s}}{\binom{2m}{m - t - s}} > \frac{t^2}{m}.
$$
For $s = 0$ this is just the theorem we already know. Let $s > 0$. Then
$$
\binom{2m}{m - s}
= \frac{m - s + 1}{m + s}\binom{2m}{m - s + 1},
$$
and
$$
\binom{2m}{m - t - s}
= \frac{m - s - t + 1}{m + s + t}\binom{2m}{m - t - s + 1}.
$$
Hence
$$
\begin{aligned}
\frac{\binom{2m}{m - s}}{\binom{2m}{m - t - s}}
&=
\frac{m - s + 1}{m + s}
\cdot
\frac{m + s + t}{m - s - t + 1}
\cdot
\frac{\binom{2m}{m - s + 1}}{\binom{2m}{m - t - s + 1}} \\
&=
\frac{(m - s + 1)(m + s + t)}{(m + s)(m - s - t + 1)}
\cdot
\frac{\binom{2m}{m - s + 1}}{\binom{2m}{m - t - s + 1}}.
\end{aligned}
$$
Since
$$
\frac{(m - s + 1)(m + s + t)}{(m + s)(m - s - t + 1)} > 1,
$$
it follows that
$$
\frac{\binom{2m}{m - s}}{\binom{2m}{m - t - s}}
>
\frac{\binom{2m}{m - s + 1}}{\binom{2m}{m - t - s + 1}}
> \frac{t^2}{m}
$$
by the induction hypothesis.

(c)
$$
\begin{aligned}
\frac{\binom{2m}{m - s}}{\binom{2m}{m - t - s}}
&=
\frac{(2m)!}{(m - s)!(m + s)!}
\cdot
\frac{(m - t - s)!(m + t + s)!}{(2m)!} \\
&=
\frac{(m + t + s)(m + t + s - 1)\cdots(m + s + 1)}{
(m - s)(m - s - 1)\cdots(m - s - t + 1)} \\
&=
\frac{m + t + s}{m - s}
\cdot
\frac{m + t + s - 1}{m - s - 1}
\cdots
\frac{m + s + 1}{m - s - t + 1} \\
&=
\left(1 + \frac{t + 2s}{m - s}\right)
\left(1 + \frac{t + 2s}{m - s - 1}\right)
\cdots
\left(1 + \frac{t}{m - s - t + 1}\right) \\
&\ge
\left(1 + \frac{t + 2s}{m}\right)^t
>
1 + t\,\frac{t + 2s}{m}.
\end{aligned}
$$
---
# 6 Fibonacci numbers

---

**6.1 Fibonacci’s exercise**

6.1. Because we use the two previous elements to compute the next.

6.1. $F_{n+1}$.

---

**6.2**

6.2. It is clear from the recurrence that two odd members are followed by an even, then by two odd.

6.2. We formulate the following statement:  
if $n$ is divisible by $5$, then so is $F_n$;  
if $n$ has remainder $1$ when divided by $5$, then $F_n$ has remainder $1$;  
if $n$ has remainder $2$ when divided by $5$, then $F_n$ has remainder $1$;  
if $n$ has remainder $3$ when divided by $5$, then $F_n$ has remainder $2$;  
if $n$ has remainder $4$ when divided by $5$, then $F_n$ has remainder $3$.  
This is then easily proved by induction on $n$.

6.2. By induction. All of them are true for $n = 1$ and $n = 2$. Assume that $n \ge 3$.

(a)
$$
\begin{aligned}
F_1 + F_3 + F_5 + \dots + F_{2n-1}
&= (F_1 + F_3 + \dots + F_{2n-3}) + F_{2n-1} \\
&= F_{2n-2} + F_{2n-1} \\
&= F_{2n}.
\end{aligned}
$$

(b)
$$
\begin{aligned}
F_0 - F_1 + F_2 - F_3 + \dots - F_{2n-1} + F_{2n}
&= (F_0 - F_1 + F_2 - \dots + F_{2n-2}) - (F_{2n-1} + F_{2n}) \\
&= (F_{2n-3} - 1) + F_{2n-2} \\
&= F_{2n-1} - 1.
\end{aligned}
$$

(c)
$$
\begin{aligned}
F_0^2 + F_1^2 + F_2^2 + \dots + F_n^2
&= (F_0^2 + F_1^2 + \dots + F_{n-1}^2) + F_n^2 \\
&= F_{n-1}F_n + F_n^2 \\
&= F_n(F_{n-1} + F_n) \\
&= F_n F_{n+1}.
\end{aligned}
$$

(d)
$$
\begin{aligned}
F_{n-1}F_{n+1} - F_n^2
&= F_{n-1}(F_{n-1} + F_n) - F_n^2 \\
&= F_{n-1}^2 + F_n(F_{n-1} - F_n) \\
&= F_{n-1}^2 - F_n F_{n-2} \\
&= -(-1)^{n-1} \\
&= (-1)^n.
\end{aligned}
$$

6.2. The identity is
$$
\binom{n}{0}
+ \binom{n-1}{1}
+ \binom{n-2}{2}
+ \dots
+ \binom{n-k}{k}
= F_{n+1},
$$
where $k = \lfloor n/2 \rfloor$.  

Proof by induction. True for $n = 0$ and $n = 1$. Let $n \ge 2$. Assume that $n$ is odd; the even case is similar, just the last term below needs a slightly different treatment.
$$
\begin{aligned}
\binom{n}{0}
+ \binom{n-1}{1}
+ \binom{n-2}{2}
+ \dots
+ \binom{n-k}{k}
&= 1 +
\Bigl(\binom{n-2}{0} + \binom{n-2}{1}\Bigr) +
\Bigl(\binom{n-3}{1} + \binom{n-3}{2}\Bigr)
+ \dots \\
&\quad +
\Bigl(\binom{n-k-1}{k-1} + \binom{n-k-1}{k}\Bigr) \\
&=
\Bigl(\binom{n-1}{0}
+ \binom{n-2}{1}
+ \binom{n-3}{2}
+ \dots
+ \binom{n-k-1}{k}\Bigr) \\
&\quad +
\Bigl(\binom{n-2}{0}
+ \binom{n-3}{1}
+ \dots
+ \binom{n-k-1}{k-1}\Bigr) \\
&= F_n + F_{n-1} \\
&= F_{n+1}.
\end{aligned}
$$

6.2. The “diagonal” is in fact a very long and narrow parallelogram with area $1$. The trick depends on the fact
$$
F_{n+1}F_{n-1} - F_n^2 = (-1)^n
$$
is very small compared to $F_n^2$.

---

**6.3 A formula for the Fibonacci numbers**

6.3. True for $n = 0, 1$. Let $n \ge 2$. Then by the induction hypothesis,
$$
\begin{aligned}
F_n &= F_{n-1} + F_{n-2} \\
&= \frac{1}{\sqrt{5}}\left[\left(\frac{1 + \sqrt{5}}{2}\right)^{n-1}
- \left(\frac{1 - \sqrt{5}}{2}\right)^{n-1}\right]
+ \frac{1}{\sqrt{5}}\left[\left(\frac{1 + \sqrt{5}}{2}\right)^{n-2}
- \left(\frac{1 - \sqrt{5}}{2}\right)^{n-2}\right] \\
&= \frac{1}{\sqrt{5}}\left[
\left(\frac{1 + \sqrt{5}}{2}\right)^{n-2}
\left(\frac{1 + \sqrt{5}}{2} + 1\right)
-
\left(\frac{1 - \sqrt{5}}{2}\right)^{n-2}
\left(\frac{1 - \sqrt{5}}{2} + 1\right)
\right] \\
&= \frac{1}{\sqrt{5}}\left[
\left(\frac{1 + \sqrt{5}}{2}\right)^n
-
\left(\frac{1 - \sqrt{5}}{2}\right)^n
\right].
\end{aligned}
$$

6.3. For $n = 0$ and $n = 1$, if we require that $H_n$ is of the given form we get
$$
H_0 = 1 = a + b, \qquad
H_1 = 3 = a \frac{1 + \sqrt{5}}{2} + b \frac{1 - \sqrt{5}}{2}.
$$
Solving for $a$ and $b$, we get
$$
a = \frac{1 + \sqrt{5}}{2}, \qquad
b = \frac{1 - \sqrt{5}}{2}.
$$
Then
$$
H_n =
\left(\frac{1 + \sqrt{5}}{2}\right)^{n+1}
+
\left(\frac{1 - \sqrt{5}}{2}\right)^{n+1}
$$
follows by induction on $n$ just like in the previous problem.

6.3.
$$
I_n = \frac{1}{2\sqrt{5}}
\bigl((2 + \sqrt{5})^n - (2 - \sqrt{5})^n\bigr).
$$
---
# 7 Combinatorial probability

---

**7.1 Events and probabilities**

7.1. The union of two events $A$ and $B$ corresponds to “$A$ or $B$”.

7.1. It is the sum of some of the probabilities of outcomes, and even if we add all we get just $1$.

7.1. $P(E) = \tfrac{1}{2}$, $P(T) = \tfrac{1}{3}$.

7.1. The same probabilities $P(s)$ are added up on both sides.

7.1. Every probability $P(s)$ with $s \in A \cap B$ is added twice on both sides; every probability $P(s)$ with $s \in A \cup B$ but $s \notin A \cap B$ is added once on both sides.

---

**7.2 Independent repetition of an experiment**

7.2. The pairs $(E, T)$, $(O, T)$, $(L, T)$ are independent. The pair $(E, O)$ is exclusive.

7.2. $P(\emptyset \cap A) = P(\emptyset) = 0 = P(\emptyset)P(A)$.  
The set $S$ also has this property: $P(S \cap A) = P(A) = P(S)P(A)$.

7.2.
$$
P(A) = \frac{|S|^{n-1}}{|S|^n} = \frac{1}{|S|}, \quad
P(B) = \frac{|S|^{n-1}}{|S|^n} = \frac{1}{|S|}, \quad
P(A \cap B) = \frac{|S|^{n-2}}{|S|^n} = \frac{1}{|S|^2} = P(A)P(B).
$$
# 8 Integers, divisors, and primes

---

**8.1 Divisibility of integers**

8.1. $a = a \cdot 1 = (-a) \cdot (-1)$.

8.1. (a) even; (b) odd; (c) $a = 0$.

8.1.  
(a) If $b = a^m$ and $c = b^n$ then $c = a^{mn}$.  
(b) If $b = a^m$ and $c = a^n$ then $b + c = a(m + n)$ and $b - c = a(m - n)$.  
(c) If $b = a^m$ and $a, b > 0$ then $m > 0$, hence $m \ge 1$ and so $b \ge a$.  
(d) Trivial if $a = 0$. Assume $a \ne 0$. If $b = a^m$ and $a = b^n$ then $a = a^{mn}$, so $mn = 1$. Hence either $m = n = 1$ or $m = n = -1$.

8.1. We have $a = cn$ and $b = cm$, hence $r = b - aq = c(m - nq)$.

8.1. We have $b = a m$, $c = a q + r$ and $c = b t + s$. Hence
$$
s = c - bt = (aq + r) - (am)t = (q - mt)a + r.
$$
Since $0 \le r < a$, the remainder of the division $s : a$ is $r$.

8.1.  
(a) $a^2 - 1 = (a - 1)(a + 1)$.  
(b) $a^n - 1 = (a - 1)(a^{n-1} + \dots + a + 1)$.

---

**8.3 Factorization into primes**

8.3. Yes, the number $2$.

8.3.  
(a) $p$ occurs in the prime factorization of $ab$, so it must occur in the prime factorization of $a$ or in the prime factorization of $b$.  
(b) $p \mid a(b/a)$, but $p \nmid a$, so by (a), we must have $p \mid (b/a)$.

8.3. Let $n = p_1 p_2 \dots p_k$; each $p_i \ge 2$, hence $n \ge 2^k$.

8.3. If $r_i = r_j$ then $i a - j a$ is divisible by $p$. But $i a - j a = (i - j)a$ and neither $a$ nor $i - j$ are divisible by $p$. Hence the $r_i$ are all different. None of them is $0$. Their number is $p - 1$, so every value $1, 2, \dots, p - 1$ must occur among the $r_i$.

8.3. For a prime $p$, the proof is the same as for $2$. If $n$ is composite but not a square, then there is a prime $p$ that occurs in the prime factorization of $n$ an odd number of times. We can repeat the proof by looking at this $p$.

8.3. Fact: If $\sqrt[k]{n}$ is not an integer then it is irrational.  

Proof: there is a prime $p$ that occurs in the prime factorization of $n$, say $t$ times, where $k \nmid t$. If (indirect assumption) $\sqrt[k]{n} = a/b$ then
$$
n\,b^k = a^k,
$$
and so the number of times $p$ occurs in the prime factorization of the left-hand side is not divisible by $k$, while the number of times it occurs in the prime factorization of the right-hand side is divisible by $k$. A contradiction.

---

**8.5 Fermat’s “Little” Theorem**

8.5.  
$$
4 \nmid \binom{4}{2} = 6.
$$
$$
4 \nmid 2^4 - 2 - 1^4.
$$

8.5.  
(a) What we need is that each of the $p$ rotated copies of a set are different. Suppose that there is a set which occurs $a$ times. Then trivially every other set occurs $a$ times. But then $a \mid p$, so we must have $a = 1$ or $p$. If all $p$ rotated copies are the same then trivially either $k = 0$ or $k = p$, which were excluded. So we have $a = 1$ as claimed.  
(b) Consider the set of two opposite vertices of a square.  
(c) If each box contains $p$ subsets of size $k$, the total number of subsets must be divisible by $p$.

8.5. We consider each number to have $p$ digits, by adding zeros at the front if necessary. We get $p$ numbers from each number $a$ by cyclic shift. These are all the same when all digits of $a$ are the same, but all different otherwise (why? the assumption that $p$ is a prime is needed here!). So we get $a^p - a$ numbers that are divided into classes of size $p$. Thus $p \mid (a^p - a)$.

8.5. Assume that $\gcd(a, p) = 1$. Consider the product
$$
a(2a)(3a)\dots((p-1)a) = (p-1)! \, a^{p-1}.
$$
Let $r_i$ be the remainder of $i a$ when divided by $p$. Then the product above has the same remainder when divided by $p$ as the product $r_1 r_2 \dots r_{p-1}$. But this product is just $(p - 1)!$. Hence $p$ is a divisor of
$$
(p - 1)! a^{p-1} - (p - 1)! = (p - 1)!(a^{p-1} - 1).
$$
Since $p$ is a prime, it is not a divisor of $(p - 1)!$, and so it is a divisor of $a^{p-1} - 1$.

---

**8.6 The Euclidean Algorithm**

8.6. $\gcd(a, b) \le a$, but $a$ is a common divisor, so $\gcd(a, b) = a$.

8.6. Let $d = \gcd(a, b)$. Then $d \mid a$ and $d \mid b$, and hence $d \mid (b - a)$. Thus $d$ is a common divisor of $a$ and $b - a$, and hence
$$
d \le \gcd(a, b - a).
$$
A similar argument shows the reverse inequality.

---

# 9 Graphs

---

**9.1 Even and odd degrees**

9.1. There are $2$ graphs on $2$ nodes, $8$ graphs on $3$ nodes (but only four “essentially different”), $16$ graphs on $4$ nodes (but only $11$ “essentially different”).

9.1.  
(a) No; sum of degrees must be even.  
(b) No; a node with degree $5$ must be connected to all other nodes, so we cannot have a node with degree $0$.  
(c) $12$.  
(d) $9 \cdot 7 \cdot 5 \cdot 3 \cdot 1 = 945$.

9.1. This graph, the complete graph, has $\binom{n}{2}$ edges if it has $n$ nodes.

9.1.  
(a) A path with $3$ nodes.  
(b) A star with $4$ endpoints.  
(c) The union of two paths with $3$ nodes.

9.1. In graph (a), the number of edges is $17$, the degrees are  
$9, 5, 3, 3, 2, 3, 1, 3, 2, 3$.  
In graph (b), the number of edges is $31$, the degrees are  
$9, 5, 7, 5, 8, 3, 9, 5, 7, 4$.

9.1. $\binom{10}{2} = 45$.

9.1. $2\binom{20}{2} = 2190$.

9.1. Every graph has two nodes with the same degree. Since each degree is between $0$ and $n - 1$, if all degrees were different then they would be $0, 1, 2, 3, \dots, n - 1$ (in some order). But the node with degree $n - 1$ must be connected to all the others, in particular to the node with degree $0$, which is impossible.

---

**9.2 Paths, cycles, and connectivity**

9.2. There are $8$ such graphs.

9.2. The empty graph on $n$ nodes has $2^n$ subgraphs. The triangle has $18$ subgraphs.

9.2. Yes, the proof remains valid.

9.2.  
(a) Delete any edge from a path.  
(b) Consider two nodes $u$ and $v$. The original graph contains a path connecting them. If this does not go through $e$, then it remains a path after $e$ is deleted. If it goes through $e$, then let $e = xy$, and assume that the path reaches $x$ first (when traversed from $u$ to $v$). Then in the graph after $e$ is deleted, there is a path from $u$ to $x$, and also from $x$ to $y$ (the remainder of the cycle), so there is one from $u$ to $y$. But there is also one from $y$ to $v$, so there is also a path from $u$ to $v$.

9.2.  
(a) Consider a shortest walk from $u$ to $v$; if this goes through any nodes more than once, the part of it between two passes through this node can be deleted, to make it shorter.  
(b) The two paths together form a walk from $a$ to $c$.

9.2. Let $w$ be a common node of $H_1$ and $H_2$. If you want a path between nodes $u$ and $v$ in $H$, then we can take a path from $u$ to $w$, followed by a path from $w$ to $v$, to get a walk from $u$ to $v$.

9.2. Both graphs are connected.

9.2. The union of this edge and one of these components would form a connected graph that is strictly larger than the component, contradicting the definition of a component.

9.2. If $u$ and $v$ are in the same connected component, then this component, and hence $G$ too, contains a path connecting them. Conversely, if there is a path $P$ in $G$ connecting $u$ and $v$, then this path is a connected subgraph, and a maximal connected subgraph containing $P$ is a connected component containing $u$ and $v$.

9.2. Assume that the graph is not connected and let a connected component $H$ of it have $k$ nodes. Then $H$ has at most $\binom{k}{2}$ edges. The rest of the graph has at most $\binom{n-k}{2}$ edges. Then the number of edges is at most
$$
\binom{k}{2} + \binom{n-k}{2}
= \binom{n-1}{2} - \frac{(k - 1)(n - k - 1)}{2}
\le \binom{n-1}{2}.
$$
---
# 10 Trees

---

**10.**

10. If $G$ is a tree then it contains no cycles (by definition), but adding any new edge creates a cycle (with the path in the tree connecting the endpoints of the new edge). Conversely, if a graph has no cycles but adding any edge creates a cycle, then it is connected (two nodes $u$ and $v$ are either connected by an edge, or else adding an edge connecting them creates a cycle, which contains a path between $u$ and $v$ in the old graph), and therefore it is a tree.

11. If $u$ and $v$ are in the same connected component, then the new edge $uv$ forms a cycle with the path connecting $u$ and $v$ in the old graph. If joining $u$ and $v$ by a new edge creates a cycle, then the rest of this cycle is a path between $u$ and $v$, and hence $u$ and $v$ are in the same component.

12. Assume that $G$ is a tree. Then there is at least one path between two nodes, by connectivity. But there cannot be two paths, since then we would get a cycle (find the node $v$ where the two paths branch away, and follow the second path until it hits the first path again; follow the first path back to $v$, to get a cycle).  

Conversely, assume that there is a unique path between each pair of nodes. Then the graph is connected (since there is a path) and cannot contain a cycle (since two nodes on the cycle would have at least two paths between them).

---

**10.1 How to grow a tree?**

10.1. Start the path from a node of degree $1$.

10.1. Any edge has only one lord, since if there were two, they would have to start from different ends, and they would then have two ways to get to the King. Similarly, an edge with no lord would have to lead to two different ways.

10.1. Start at any node $v$. If one of the branches at this node contains more than half of all nodes, move along the edge leading to this branch. Repeat. You will never backtrack because this would mean that there is an edge whose deletion results in two connected components, both containing more than half of the nodes. You will never cycle back to a node already seen because the graph is a tree. Therefore you must get stuck at a node such that each branch at this node contains at most half of all nodes.

---

**10.2 Rooted trees**

---

**10.3**

10.3. The number of unlabeled trees on $2,3,4,5$ nodes is $1,1,2,3$. They give rise to a total of $1,2,16,125$ labeled trees.

10.3. There are $n$ stars and $n!/2$ paths on $n$ nodes.

---

**10.4 How to store a tree?**

10.4. The first is the father code of a path; the third is the father code of a star. The other two are not father codes of trees.

10.4. This is the number of possible father codes.

10.4. Define a graph on $\{1, \dots, n\}$ by connecting all pairs of nodes in the same column. If we do it backwards, starting with the last column, we get a procedure of growing a tree by adding a new node and an edge connecting it to an old node.

10.4. (a) encodes a path; (b) encodes a star; (c) does not encode any tree (there are more $0$’s than $1$’s among the first $5$ elements, which is impossible in the planar code of any tree).

---

# 11 Finding the optimum

---

**11.1 Finding the best tree**

11.1. Let $H$ be an optimal tree and let $G$ be the tree constructed by the pessimistic government. Look at the first step when an edge $e = uv$ of $H$ is eliminated. Deleting $e$ from $H$ we get two components; since $G$ is connected, it has an edge $f$ connecting these two components. The edge $f$ cannot be more expensive than $e$, else the pessimistic government would have chosen $f$ to eliminate instead of $e$. But then we can replace $e$ by $f$ in $H$ without increasing its cost. Hence we conclude as in the proof given above.

11.1. Very similar.

11.1. Very similar.

11.1. Take nodes $1,2,3,4$ and costs  
$c(12) = c(23) = c(34) = c(41) = 3$, $c(13) = 4$, $c(24) = 1$.  
The pessimistic government builds $(12341)$, while the best solution is $12431$.

---

**11.2 Traveling Salesman**

11.2. No, because it intersects itself (see next exercise).

11.2. Replacing two intersecting edges by two other edges pairing up the same $4$ nodes, just differently, gives a shorter tour by the triangle inequality.

---

# 12 Matchings in graphs

---

**12.1 A dancing problem**

12.1. If every degree is $d$, then the number of edges is $d \cdot |A|$, but also $d \cdot |B|$.

12.1. (a) A triangle. (b) A star.

12.1. A graph in which every node has degree $2$ is the union of disjoint cycles. If the graph is bipartite, these cycles have even length.

---

**12.3**

12.3. Let $X \subseteq A$ and let $Y$ denote the set of neighbors of $X$ in $B$. There are exactly $d|X|$ edges starting from $X$. Every node in $Y$ accommodates no more than $d$ of these; hence $|Y| \ge |X|$.

---

**12.4**

12.4. On a path with $4$ nodes, we may select the middle edge.

12.4. The edges in $M$ must meet every edge in $G$, in particular every edge in the perfect matching. So every edge in the perfect matching has at most one endpoint unmatched by $M$.

12.4. The largest matching has $5$ edges.

12.4. If the algorithm terminates without a perfect matching, then the set $S$ shows that the graph is not “good”.

---

**12.5**

12.5. The first graph does; the second does not.
