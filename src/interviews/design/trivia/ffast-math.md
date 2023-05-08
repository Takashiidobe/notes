18. What is ffast-math?

- Breaks IEEE compliance: allows reordering of floating point instructions, which can lead to small errors.
- Second, it disables setting errno after single-instruction math functions, which can double performance.
- Third, it makes the assumption that all math is finite, which means that no checks for NaN (or zero) are made in place where they would have detrimental effects. It is simply assumed that this isn't going to happen.
- Fourth, it enables reciprocal approximations for division and reciprocal square root.
- Further, it disables signed zero (code assumes signed zero does not exist, even if the target supports it) and rounding math, which enables among other things constant folding at compile-time.
- Last, it generates code that assumes that no hardware interrupts can happen due to signalling/trapping math (that is, if these cannot be disabled on the target architecture and consequently do happen, they will not be handled).
