---
title: "Regularization"
---

# Regularization

Prev: [generalization](generalization.md)
Next: [understanding-principal-component-analysis](understanding-principal-component-analysis.md)

## The Context and Intuition behind Regularization

If you have a dataset and a class of models you are trying to fit, regularization is a technique to form some preferences about the models in the chosen class, and return a model that takes into account both its preference and how well it fits.

As an example, imagine $n$ points, $x_1,\dots,x_n \in \Bbb R^d$ with $n$ labels, $y_1,\dots,y_n \in \Bbb R$. Take this $l_2$ regularized least-squares object function corresponding to a model $a \in \Bbb R^d$:

$$f(a) = \displaystyle \sum_{i=1}^n((a,x_i) - y_i)^2 + \lambda \vert a \vert_2^2$$

$\vert a \vert_2^2$ denotes the squared Euclidean length of the vector $a$, and $\lambda$ dictates how much the models with the small $l_2$ should be prioritized. As $\lambda$ increases, models with smaller $a$ will be more heavily prioritized.

Many common forms of regularization are viewed as prioritizing different notions of "simple" models. $l_2$ regularization is common, as are sparsity inducing models, that favor sparser coefficients.

Some regularizers are implicit, where the algorithm you use to find a model to fit the data, like stochastic gradient descent, prefers some hypotheses to others.

Why regularize at all? If $n \gg d$, then just use ERM. Otherwise, if $k \approx n$, then ERM will not generalize, as it'll overfit the data. You'll need some way to make your model generalize, and regularization is one way of encoding additional information, or preferences about the form of the true underlying model, that can be applied and amerliorate the overfitting.

## Increasing Dimensionality: the Polynomial Embedding and Random Non-Linear Features

One viewpoint is to always have your models where $n \gg d$, so there's sufficient expressivity so that ERM generalizes.

Another viewpoint is that models with more features are simply more expressive, hence, it's wasteful to only train models that are $n \gg d$. You should keep adding features until the dimensionality, $d$ becomes $d'$, where $d' \approx n$. The intuition is that for most problems, the model is complex, and capturing more dimensions of it will only aid your model.

Of course, it depends -- if your underlying problem is very simple, neither more data nor more dimensions really help -- but for more complicated problems, they help a lot.

Thus, we need to know how to increase dimensionality, by learning a linear classifier or regression in the larger-dimensional space.

### The Polynomial Embedding

One way to increase the dimensionality of a datapoint $x = (x_1,\dots,x_d)$ is to add a number of polynomial features. For example, adding $\begin{pmatrix}d \\ 2 \end{pmatrix}$ coordinates, corresponding to the $\begin{pmatrix}d \\ 2 \end{pmatrix}$ products of pairs of coordinates of the original data. This is a quadratic embedding. This embedding, $f : \Bbb R^d \to \Bbb R^{d + d(d+1) / 2}$ is defined as follows:

$$f(x) = (x_1,\dots,x_d,x_1^2,x_1 x_2,x_1 x_3,\dots,x_d x_{d-1},x_d^2)$$

A linear function in this quadratic space is more expressive than a linear function in the original space. A linear function in this new space would be capable of modeling functions $g(x) = (x_1 + x_2 + x_17)^2$.

You can train linear classifiers in polynomial spaces by mapping the data into the new space and proceeding as usual. It is also possible to do this without writing out the higher-dimensional embedding of the data. This is also called *kernelization*.

### A Random Projection plus Nonlinearity

A different method might be like the JL transformation, but by mapping from fewer to more dimensions. To complete the mapping $f : \Bbb R^d \to \Bbb R^{d'}$, choose a $d' x d$ matrix $M$, select each index independently from a standard Gaussian, and then defining a transformation function, $f(x) = Mx$.

This embedding increases the dimensionality of the data, but if all the data are mapped in this way, the functions compose, and this is just a linear function of the original space in higher dimensions.

To increase the expressivity of linear functions in this space, you need a non-linear operation, and apply it to each coordinate in $Mx$. Squaring each coordinate, taking the absolute value, the square root, etc.

This is what a neural net does.

### Comparing Polynomial Embedding vs Random Projection + Nonlinearity

You might pick polynomial embedding when you want a basis-dependent embedding or not. If the features of the input space are meaningful, then a polynomial embedding makes sense -- if your model has features that model the real world, and they are real features like mass or light, then it would be reasonable to preserve the interpretability of the new features. If your features are not distinct, or chosen arbitrarily, then the random projection that is rotationally invariant might make more sense.

## Regularization: The Bayesian and Frequentist viewpoints

### The Bayesian View and $l_2$ Regularization

Under Bayes, the true model underlying the data is drawn from some known prior distribution. Given this, you can evaluate the likelihood of a given model.

### The Frequentist View and $l_0$ Regularization

The frequentist approach to justifying regularization is to argue if the true model has a specific property, then regularization will allow you to recover a good approximation to the true model.

A good linear model might possess the characteristic of sparsity. We can then design a regularizer that prefers sparser models, allowing for a simpler model even when the amount of available data is significantly less than what would be required to learn a dense linear model.

### $l_0$ regularization

If we prefer sparse models, the most natural regularizer is to penalize vectors that are non-sparse. This is the $l_0$ regularizer. In regularized least squares, the objective function would be:

$$f(a) = \displaystyle \sum_{i=1}^n((a,x_i) - y_i)^2 + \lambda \vert a \vert_0$$

The problem with this is that $l_0$ norm is highly discontinuous, so changing $a$ by a small amount can change $\vert a \vert_0$ by 1.

### $l_1$ as a computationally tractable proxy for $l_0$

In practice, the $l_1$ norm is used as a proxy for the $l_0$ norm. This is a vector of the sum of the absolute values of the coordinates, so it is continuous and linear. That looks like this:

$$f(a) = \displaystyle \sum_{i=1}^n((a,x_i) - y_i)^2 + \lambda \vert a \vert_1$$

This is better because it is amenable to gradient-descent, and other optimization approaches.

This leads to the following proposition:

Given $n$ independent Gaussian vectors $x_1,\dots,x_n \in \Bbb R^d$, consider labels $y_i = (a,x_i)$ for some vector $a$ with $\vert a \vert_0 = s$. The minimizer of the $l_1$ regularized objective function, will be the vector $a$ with high probability, provided that $n \gt c * s \log{} d$ for some absolute constant $c$.

Prev: [generalization](generalization.md)
Next: [understanding-principal-component-analysis](understanding-principal-component-analysis.md)
