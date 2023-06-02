---
title: "Principles of experimental design"
---

# Principles of experimental design

Next: [test-statistics-and-randomization-distributions](test-statistics-and-randomization-distributions.md)

## Induction

Much of our knowledge has to do with reasoning from specific cases to the general case.

We might design an experiment that samples some part of the population, asks them a question, and then generalize that to the whole population.

For example, asking 200 people on a telephone survey, to get information on the opinion of the entire city.

## Model of a process or System

Our interest is in how the input(s) of a process affect the output(s). Input variables consist of:

- **controllable factors** $x_1$: factors measured and changed by the scientist
- **uncontrollable factors** $x_2$: factors measured but not changed by the scientist
- **noise factors** $e$: unmeasured, uncontrolled factors, called variability or error.

For any interesting process, there are inputs such that:

$$ variability in input \to variability in output $$

If variability in an input factor $x$ leads to variability in output $y$, $x$ is considered a source of variation.

## Experiments and observational studies

Information on how inputs affect output can be gained from:

- **Observational Studies**: Input and output variabels are observed from a pre-existing population. It is hard to discern what is input and what is output.
- **Controlled Experiments**: One or more input variables are controlled and manipulated by the experimenter to determine their effect on the output.

### Example

- Population: Healthy, post-menopausal women in the U.S.

- Input variables:
    1. estrogen treatment, yes/no
    2. demographic variables (age, race, diet, etc.)
    3. unmeasured variables (?)

- Output variables:
    1. coronary heart disease
    2. invasive breast cancer
    3. other health related outcomes

- Question: How does estrogen treatment affect health outcomes?

**Observational Study**:

1. **Population**: 93,676 women enlisted starting in 1991, tracked over eight years on average.
2. **Results**: good/low rates of coronary heart disease generally associated with estrogen treatment.
3. **Conclusion**: Estrogen treatment is postively associated with health outcomes, such as prevalence of heart disease.

**Experimental Study (Randomized Controlled)**:

1. **Experimental population**:
    - 373,092 women determined to be eligible
    - 18,845 provided consent to be in experiment
    - 16,608 included in experiment

The design was the following:

$$\max(a,b)=\begin{cases}x=1&(\text{ estrogen treatment})\\x=0&(\text{ no estrogen treatment})\end{cases}$$

Women were of different ages and treated at different clinics. Thusly, women were blocked together by age and clinic, and treatments were randomly assigned within each block of (age x treatment). This is called a **randomized block** design.

|          | (50-59) | (60-69) | (70-79) |
|----------|---------|---------|---------|
| clinic 1 | $n_11$  | $n_12$  | $n_13$  |
| clinic 2 | $n_21$  | $n_22$  | $n_23$  |
| ...      | ...     | ...     | ...     |

2. **Results**:

Women on treatment had a higher incidence rate of:

- Heart Disease
- Breast cancer
- Stroke
- Pulmonary embolism

And a lower incidence rate of:

- colorectal cancer
- hip fracture

3. **Conclusion**:

- Estrogen treatment is not a viable preventative measure for heart disease in the general population. Thus, we infer based on our treatment population, that if the general population were treated, heart disease rates would increase.

**Question**: Why did the two studies have different conclusions?

Consider the following explanation:

$x$ = estrogen treatment
$e$ = "health consciousness" (not measured)
$y$ = health outcomes

```
     e
    v  v
   x -> y
(correlation)
```

Association between $x$ and $y$ may be due to an unmeasured variable, $e$.

```
                e
           v         v
(randomization)
x -------------------> y
(correlation = causation)
```

Randomization breaks the association between $e$ and $x$.

Observational studies can suggest good experiments to run, but cannot show *causation*.

Randomization can eliminate correlation between $x$ and $y$ due to a different cause, $e$, a confounder.

"No Causation without randomization"

## Steps in Designing an Experiment

1. Make a hypotheses
2. Choose an experimental unit, which are units to be randomized under treatment
3. Choose an output variable
4. Determine sources of variation in response
    - factors of interest
    - nuisance factors
5. Decide which variables to measure and control:
    - treatment variables
    - sources of variation (blocking variables)
6. Decide on the procedure and how treatments are randomly assigned


### Three principles of Experimental Design

**Replication**: More repetition = better inference

The more experiments you run, the better your inference becomes

**Randomization**: Random assignment of treatments to experimental units. This removes potential for systematic bias. It also makes confounding by an unobserved variable unlikely, but not impossible.

**Blocking**: Randomization within blocks of homoegeneous experimental units. This allows for evenly distributed treatments across large potential sources of variation.




Next: [test-statistics-and-randomization-distributions](test-statistics-and-randomization-distributions.md)
