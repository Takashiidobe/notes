---
title: "Tensor methods"
---

# Tensor methods

Prev: [low-rank-matrix-approximations](low-rank-matrix-approximations.md)
Next: [graphs-as-matrices-and-the-laplacian-of-a-graph](graphs-as-matrices-and-the-laplacian-of-a-graph.md)

## Introduction to Tensors

A tensor is like a matrix, but with more dimensions.

**Definition 1.1**: An $n_1 * \dots * n_k$ tensor is a set of $n_1 \dot n_2 \dot \dots \dot n_k$ numbers, which is in a $k$-dimensional hypercube. With this $k$-tensor, $A$, a specific element can be referred to via $A_{i_1,i_2,\dots,i_k}$.

A 2-tensor is simply a matrix with $A_{i,j}$ referring to the $i$,$j$th entry. An $n_1 x n_2 x n_3$ tensor is a stack of $n_3$ matrices, where each matrix has size $n_1 x n_2$. The entry $A_{i,j,k}$ of a 3-tensor will refer to the $i$,$j$th entry of the $k$th matrix in the stack.

**Remark 1.2**: Tensors are useful in physics, and viewed as geometric objects.

### Examples of Tensors

**Example 1.3 (k-grams)**: Given a body of text, and some ordering of the set of words, like alphabetical ordering, a $k$-tensor $A$ is defined by setting entry $A_i,\dots,i_k$ equal to the number of times the sequence of words $w_{i_1},w_{i_2},\dots,w_{i_k}$ occurs in the text. With $n$ distinct words, we can extract an $n x n x n$ 3-tensor where $A_{i,j,k}$ represents the number of times in the corpus that the $i$th, $j$th, and $k$th words occur in sequence.

**Example 1.4 (The Moment Tensor)**: Suppose we have some data, $s_1,s_2,\dots,s_n$ representing independent draws from a high-dimensional distribution, $\Bbb R^{d}$, so $s_i \in \Bbb R^{d}$. The mean of the data is a vector of length $d$. The covariance matrix of this data is a $d x d$ matrix, where the $i,j$th entry is an empirical estimate of $\Bbb E [(X_i, - \Bbb E[X_i])(X_j - E[X_j])]$, where $X_i$ denotes the $i$th coordinate of a sample from the distribution. The $d x d x d$ 3-tensor representing the third order moments, has entries $A_{i,j,k}$ representing the estimate of $\Bbb E [(X_i, - \Bbb E[X_i])(X_j - E[X_j])[(X_k - \Bbb E[X_k])]]$. This is generalizable to $k$ dimensions.

$$ M_{i,j,k} = \frac{1}{n} \displaystyle \sum_{i=1}^n (s_{l_i} - m_i)(s_{l_j} - m_j)(s_{l_k} - m_k) $$

### The Rank of a Tensor

The rank of a tensor is similar to the rank of a matrix. A matrix $M$ has rank $r$ if it can be written as $M = UV^t$ where $U$ has $r$ columns and $V$ has $r$ columns. Letting $u_1,\dots,u_r$ and $v_1,\dots,v_r$ denote these columns, we have:

$$ M = \displaystyle \sum_{i=1}^r u_i,u_i^t $$

Each term $u_iv_i^t$ is the outer product of two vectors. $M$ is represented as a sum of $r$ rank one matrices, where the $i$th matrix $B_i = u_iv_i^t$ has entries $B_{j,k} = u_i(j)v_i(k)$, the product of the $j$th entry of the vector $u_i$ and the $k$th entry of vector $v_i$.

A tensor has rank 1 if it can be expressed as the outer-product of a set of vectors, and is rank $k$ if it can be written as a sum of $k$ rank 1 tensors.

**Definition 1.5** With vectors $u$, $v$, $w$ of lengths $n$, $m$, and $l$, their outer product is the $n x m x l$ rank one 3-tensor denoted $A = u \otimes v \otimes w$ with entries $A_{i,j,k} = u_iv_jw_k$

Or for higher dimensional tensors:

**Definition 1.6** Given vectors $v_1,v_2,\dots,v_k$ of lengths $n_1,n_2,\dots,n_k$ their outer product is denoted as $v_1 \otimes v_2 \otimes \dots \otimes v_k$, and represents the $n_1 x n_2 x \dots x n_k$ $k$-tensor $A$ with entry $A_{i1,i2,\dots,ik} = v_1(i_1) \dot v_2(i_2) \dot \dots \dot v_k(i_k)$.

**Example 1.7** Given the following:

$$ v_1 = \begin{pmatrix} 1 \\ 2 \\ 3 \end{pmatrix}, v_2 = \begin{pmatrix} -1 \\ 1 \end{pmatrix}, v_3 = \begin{pmatrix} 10 \\ 20 \end{pmatrix} $$

$v_1 \otimes v_2 \otimes v_3$ is a 3 x 2 x 2 3-tensor, which can be decomposed into two 3 x 2 matrices.

$$ M_1 = \begin{pmatrix} -10 & 10 \\ -20 & 20 \\ -30 & 30 \end{pmatrix}, M_2 = \begin{pmatrix} -20 & 20 \\ -40 & 40 \\ -60 & 60 \end{pmatrix} $$

**Definition 1.8** A 3-tensor A has rank $r$ if there exists 3 sets of $r$ vectors $u_1,\dots,u_r$, $v_1,\dots,v_r$, and $w_1,\dots,w_r$ where

$$ A = \displaystyle \sum_{i=1}^r u_i \otimes v_i \otimes w_i $$

$k$-tensors are the same.

## Differences between Matrices and Tensors

Most operations on matrices do not apply to $k$-tensors for $k \geq 3$. Some differences:

1. For matrices, the best rank-$k$ approximation can be found by iteratively finding the best rank-1 approximation, and then substractin git off. Thus, for a matrix $M$, the best rank 1 approximation of $M$ is the same as the best rank 1 approximation of the matrix $M_2$ defined as the best rank 2 approximation of $M$. Thus, if $uv^t$ is the best rank 1 approximation of $M$, then $rank(M - uv^t) = rank(M - 1)$. For $k$-tensors with $k geq 3$, this is not the case.
2. There is no way no describe an explicit construction of $n x n x n$ tensors whose rank is greater than $n^{1.1}$ for all $n$.
3. Computing the rank of matrices is easy, but the rank of 3-tensors is NP-hard.
4. Despite being NP-hard, if the rank of a3-tensor is small, then:
    1. It can be efficiently computed.
    2. Its low-rank representation is unique.
    3. It can be efficiently recovered.

## Low-Rank Tensors

A low-rank representation of matrix $M$ is not unique. One pioneer of low-rank approximation matrices was Spearman. He gave a number of academic tests to a number of students, and formed a matrix $M$ in which entry $M_{i,j}$ represented the performance of the $i$th student on the $j$th test. He figured that $M$ was close to a rank 2 matrix, and gave the following explanation. Assume the $i$th student has two numbers, $m_i$ and $v_i$ denoating mathematical and verbal ability. Suppose that each test, $j$ can be reduced to two numbers, $t_{m_j}$ and $t_{v_j}$, both denoting the mathematical and verbal components. If this was correct, then $M_{i,j} \approx m_i t_j + v_i q_j$, and so $M$ would be close to the rank 2 matrix $UV^t$, where the two columns $U$ represent the two vectors that represent math/verbal abilities, and the two columns of V represent the tests' math/verbal components. Unfortunately, this is not unique, so even if this was true, the rank 2 representation would not correspond to this model.

**Theorem 3.1** Given a 3-tensor $A$ of rank $k$ there exists three sets of linearly independent vectors, (u_1,\dots,u_k),(v_1,\dots,v_k),(w_1,\dots,w_k) where:

$$ A = \displaystyle \sum_{i=1}^k u_i \otimes v_i \otimes w_i $$

And this rank $k$ decomposition is unique, (up to scaling the vectors by a constant) and thus the factors can be efficiently recovered.

Take spearman's experiment with an extra dimension, where students were in three different settings, (classical music playing, distracting music playing, control). Then, let $M$ denote the corresponding 3-tensor, with $M_{i,j,k}$ being the performance of student $i$ on test $j$ in setting $k$.

Suppose the true model of the world is the following: for every student there are two numbers representing their math/verbal ability, and every test can have some mix of a math and verbal component. As well, each setting scales the math and verbal performance of each student. Thus, $M_{i,j,k}$ can be approximated by multiplying the math ability of the student with the math component of the test and the math boost-factor of the setting, with the same done for the verbal components.

Assuming that the vector of student math abilities are not identical to the vector of student verbal abilities, and the 2 vectors of math/verbal test components are not identical up to rescaling, and the 2 vectors of math/verbal setting boosts are not identical up to rescaling, this is the unique factorization of the tensor, and we can recover the exact factors.

### Quick Discussion

As long as the factors that are used for a tensor are linearly independent, then the factors can be recovered uniqely. Thus, they can be used to enable useful features to be extracted from data in an unsupervised setting.

### The Algorithm

The algorithm in 3.1 is often called Jenrich's Algorithm.

**Algorithm 1**: Tensor Decomposition

Given an $n x n x n$ tensor $A = \displaystyle \sum{i=1}^k u_i \otimes v_i \otimes w_i$ with $(u_1,\dots,u_k)$ and $(v_1,\dots,v_k)$ and $(w_1,\dots,w_k)$ being lienarly independent, the following algorithm will output the lists of $u$'s, $v$'s, and $w$'s.

- Choose random unit vectors, $x, y \in \Bbb R^n$
- Define the $n x n$ matrices $A_x,A_y$ where $A_x$ is defined as follows: consider $A$ as a stack of $n n x n$ matrices, where $A_x$ is the weighted sum of these $n$ matrices, where the weight for the $i$th matrix is $x_i$. $A_y$ is analogously defined, with the $i$th matrix being scaled by $y_i$.
- Compute the eigen-decompositions of $A_xA_y^{-1} = QSQ^{-1}$, and $A_x^{-1}A_y = (Y^k)^{-1}TY^t$.
- With probability 1, the entries of the diagonal matrix $S$ is unique, and will be inverses of the entries of diagonal matrix $T$. The vectors $u_1,\dots,u_k$ will be the columns of $Y$, where $v_i$ is the reciprocal of the eigenvalue of $u_i$.
- Given the $u_i$'s and $v_i$'s, we can solve a linear system to find the $w_i$'s.

Prev: [low-rank-matrix-approximations](low-rank-matrix-approximations.md)
Next: [graphs-as-matrices-and-the-laplacian-of-a-graph](graphs-as-matrices-and-the-laplacian-of-a-graph.md)
