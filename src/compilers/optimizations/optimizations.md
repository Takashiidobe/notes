---
title: Compiler Optimizations
date created: Tuesday, April 9th 2024, 7:37:44 pm
date modified: Monday, November 25th 2024, 8:23:57 pm
---
# Compiler Optimizations

1. Peephole Optimization

Description: This involves looking at small sets of instructions (the
"peephole") to find patterns that can be replaced with more efficient ones. It
can easily catch and eliminate redundant push/pop operations, replace them with
register moves, or even remove them if they are unnecessary.
Example: Converting a push followed by a pop into a direct register-to-register
move.

Original, Non-Optimized Code

Consider this simple snippet, which is intentionally verbose for demonstration
purposes. It performs operations that could be simplified with peephole
optimization.

```asm
.section .data
value: .int 10            # An example value

.section .text
.globl _start

_start:
    mov $0, %eax          # Clear %eax register
    add $0, %eax          # Add 0 to %eax, unnecessary operation

    mov value, %ebx       # Move 'value' into %ebx
    add $0, %ebx          # Add 0 to %ebx, another unnecessary operation

    mov %ebx, %ecx        # Move %ebx to %ecx
    sub %eax, %ecx        # Subtract %eax from %ecx, where %eax is 0, so it's
                          # redundant

    # Assume %ecx now has the result to be used further
    mov %ecx, %edx        # Move result to %edx
    mov %edx, %esi        # Move %edx to %esi without changing the value

    # Exit sequence (simplified)
    mov $60, %eax     # syscall: sys_exit
    xor %edi, %edi    # status 0
    syscall
```

Optimized Version with Peephole Optimization

Now, let's apply peephole optimizations to simplify the above code. The
optimizations will remove unnecessary operations and consolidate moves where
possible.

```asm
.section .data
value: .int 10            # An example value

.section .text
.globl _start

_start:
    mov value, %esi       # Directly move 'value' into %esi for use, skipping
                          # %ebx and %ecx

    # The original sequence involving %eax, %ebx, and %ecx was redundant and
    # has been removed.
    # This directly uses %esi for whatever purpose %ecx was initially intended,
    # assuming it doesn't
    # disrupt the program logic based on the further use of %ecx in the
    # original code.

    # Exit sequence (simplified)
    mov $60, %eax     # syscall: sys_exit
    xor %edi, %edi    # status 0
    syscall
```

Explanation of Optimizations Applied

Removed Redundant Zero Additions: Instructions that add 0 to a register,
effectively doing nothing, were removed. This is a common target for peephole
optimizations.
Eliminated Unnecessary Moves: Instead of moving the value through several
registers (%ebx to %ecx, then %ecx to %edx, and finally %edx to %esi), the
optimized code directly moves the initial value into %esi. This reduces the
number of instructions and register usage.
Skipped Redundant Clearing and Subtraction: The original code cleared %eax and
then used it in a subtraction that would not change the result. These
operations were removed.

Benefits of Peephole Optimization

Reduced Instruction Count: Fewer instructions mean the CPU has less work to do,
potentially leading to faster execution times.
Improved Readability: By removing unnecessary operations, the remaining code is
more straightforward and easier to understand.
Efficient Use of Registers: Reducing unnecessary data moves between registers
frees up those registers for other uses and may help avoid spills to memory in
more complex scenarios.

2. Register Allocation

Description: This optimization assigns variables to machine registers as much
as possible and for as long as possible, reducing the need to push and pop
temporary variables onto the stack.
Technique: Graph coloring algorithms are often used to efficiently allocate
variables to a limited number of registers, minimizing spills to memory.

- Identify the live ranges of variables, which are the portions of the program
where each variable is used.
- Allocate registers to those variables in a way that minimizes the need to
load and store variables from memory, known as spilling.
- Spill some variables to memory when there are not enough registers available
to hold all the active variables.

Graph Coloring for Register Allocation

One popular method for register allocation is graph coloring. Here's how it
typically works:

Interference Graph Construction: The compiler builds an interference graph
where each node represents a variable, and an edge between two nodes indicates
that the variables are live at the same time and thus cannot share the same
register.

Graph Coloring: The compiler attempts to color each node in this graph with a
color representing a register. The rule is that no two nodes connected by an
edge can have the same color, reflecting the constraint that no two variables
that interfere (are live at the same time) can be in the same register. The
goal is to color the graph with the fewest colors possible, with the ideal
being to use a number of colors (registers) equal to or less than the number of
available registers.

Spilling: If the graph cannot be colored with the available number of colors
(registers), some variables will need to be "spilled" to memory. The compiler
might then rewrite parts of the program to use memory for those variables and
try the coloring again.

Example of Register Allocation

Consider a simple program segment:

```c
int a = 10;
int b = 20;
int c = a + b;
int d = a - b;
```

For this program, the compiler would:

Analyze Usage: Determine the live ranges of a, b, c, and d. a and b are live
until after d is calculated.
Assign Registers: If only two registers are available, the compiler might
assign a and b to the two registers initially, then store the result of a + b
in c (in memory or a register, if one becomes available after a and b are no
longer needed), and similarly for d.

3. Dead Code Elimination

Description: Removes code that does not affect the program's output, including
unnecessary stack operations that have no impact on subsequent computations.
Effect: This can significantly reduce the size of the compiled code and improve
cache usage by eliminating needless instructions.

4. Function Inlining

Description: Replaces a function call with a copy of the function's body
directly in the caller's code. This can often eliminate the overhead of setting
up and tearing down the stack frame for function calls that are small or called
frequently.
Benefit: Reduces the need for pushing arguments and frame pointers onto the
stack, although it needs to be balanced with the increased code size.

5. Loop Invariant Code Motion

Description: Moves calculations that produce the same result every iteration of
a loop (invariants) outside the loop. This can reduce the number of push/pop
operations inside the loop if variables are moved to registers.
Example: Moving a constant calculation out of a loop, thereby avoiding repeated
stack manipulations.

Non-Optimized Version:

```asm
.section .data
array: .int 1,2,3,4,5     # Example array of integers
length: .int 5            # Length of the array

.section .text
.globl _start

_start:
    mov $0, %rdi          # Loop index (i)
    mov $0, %rax          # Sum
    mov $10, %rbx         # Invariant: a constant to add to sum each iteration

loop_start:
    cmp %rdi, length      # Compare loop index with array length
    je loop_end           # Jump to end if equal

    mov array(, %rdi, 4), %rcx  # Load array[i] into %rcx
    add %rcx, %rax             # Add array[i] to sum
    add %rbx, %rax             # Add invariant to sum (inefficient here)

    inc %rdi                   # Increment loop index
    jmp loop_start             # Jump back to start of loop

loop_end:
    # %rax now contains the final sum
    # Exit the program (simplified for this example)
    mov $60, %rax     # syscall: sys_exit
    xor %rdi, %rdi    # status 0
    syscall
```

Optimized Version:

```asm
.section .data
array: .int 1,2,3,4,5     # Example array of integers
length: .int 5            # Length of the array

.section .text
.globl _start

_start:
    mov $0, %rdi                  # Loop index (i)
    mov $0, %rax                  # Sum
    mov $10, %rbx                 # Invariant: a constant to add to sum
    imul $5, %rbx, %rbx           # Multiply invariant by loop count outside
                                  # loop (Loop Invariant Code Motion)

loop_start:
    cmp %rdi, length              # Compare loop index with array length
    je loop_end                   # Jump to end if equal

    mov array(, %rdi, 4), %rcx    # Load array[i] into %rcx
    add %rcx, %rax                # Add array[i] to sum

    inc %rdi                      # Increment loop index
    jmp loop_start                # Jump back to start of loop

loop_end:
    add %rbx, %rax                # Add modified invariant to sum after the loop

    # %rax now contains the final sum
    # Exit the program (simplified for this example)
    mov $60, %rax     # syscall: sys_exit
    xor %rdi, %rdi    # status 0
    syscall
```

Explanation of Optimization

Original Inefficiency: In the non-optimized version, we add a constant value
(%rbx) to the sum inside the loop. This operation is invariant; it doesn't
depend on the loop's index and thus does not need to be repeated on each
iteration.

Optimization Applied: In the optimized version, we multiply the invariant
(%rbx) by the loop's iteration count (length) outside of the loop. This
effectively applies the constant addition in a single operation after the loop,
significantly reducing the amount of redundant computation.

Benefit: The primary benefit here is reducing the number of instructions
executed inside the loop, leading to faster execution, especially for large
arrays or more complex invariants.

6. Common Subexpression Elimination

Description: This identifies and eliminates duplicate expressions that are
computed more than once, storing the result in a register and reusing it, which
can reduce stack usage if these expressions involve stack operations.
Application: Useful in scenarios where multiple parts of a program perform the
same calculation with the same inputs.

7. Strength Reduction

Description: Replaces more expensive operations with cheaper ones that achieve
the same result. For stack operations, this might mean replacing operations
that manipulate the stack with simpler arithmetic operations on registers, when
applicable.
Example: Using increment (inc) instruction instead of add for counting, when
the count is stored in a register.

Strength reduction is an optimization technique used to replace expensive
operations with cheaper ones, without changing the overall effect of the code.
This is particularly useful in loops or frequently executed sections of code
where the cost of operations can add up significantly. In the context of x86_64
assembly, this often involves replacing multiplication or division operations
with additions or shifts when applicable, as the latter are generally faster.
Example Scenario: Multiplication in a Loop

Consider a loop that increments a counter by a fixed multiplier in each
iteration, an operation that can be optimized using strength reduction.
Original, Non-Optimized Code

```asm
.section .data
counter: .int 0          # Counter to increment
multiplier: .int 4       # Multiplier (e.g., we are multiplying by 4 each loop)

.section .text
.globl _start

_start:
    mov $0, %eax              # Loop index
    mov $10, %ebx             # Number of iterations
    mov counter, %ecx         # Load counter

loop_start:
    cmp %eax, %ebx            # Compare loop index with number of iterations
    je loop_end               # Jump to end if they are equal

    mov multiplier, %edx      # Load multiplier
    imul %edx, %ecx           # Multiply counter by multiplier (expensive
operation)
    mov %ecx, counter         # Store result back in counter

    inc %eax                  # Increment loop index
    jmp loop_start            # Jump back to the start of the loop

loop_end:
    # Exit sequence (simplified for example)
    mov $60, %eax         # syscall: sys_exit
    xor %edi, %edi        # status 0
    syscall
```

Optimized Version with Strength Reduction

In this optimized version, we replace the multiplication with an addition,
assuming the multiplier is a known constant and the operation is equivalent.

```asm
.section .data
counter: .int 0          # Counter to increment
increment: .int 4        # Increment value, equivalent to the multiplier but
used for addition

.section .text
.globl _start

_start:
    mov $0, %eax              # Loop index
    mov $10, %ebx             # Number of iterations
    mov counter, %ecx         # Load counter

loop_start:
    cmp %eax, %ebx            # Compare loop index with number of iterations
    je loop_end               # Jump to end if they are equal

    add increment, %ecx       # Add increment to counter (cheaper operation)
    mov %ecx, counter         # Store result back in counter

    inc %eax                  # Increment loop index
    jmp loop_start            # Jump back to the start of the loop

loop_end:
    # Exit sequence (simplified for example)
    mov $60, %eax         # syscall: sys_exit
    xor %edi, %edi        # status 0
    syscall
```

Explanation of Strength Reduction Applied

Multiplication to Addition: The original code multiplied the counter by 4
in each loop iteration, which is more expensive than addition. Knowing the
multiplier is a constant (4), we replaced the multiplication with an addition
of the same value, which is significantly faster on most CPUs.

Removed Load of Multiplier: Since the increment value doesn't change, we
can directly use the increment value in the add instruction, removing the need
to load the multiplier each time through the loop.

8. Instruction Scheduling

Description: Reorders instructions to improve CPU pipeline efficiency without
changing the program's output. This can sometimes involve rearranging stack
operations to minimize the number of instructions that the CPU is waiting on.
Benefit: Improves overall execution speed and can indirectly reduce the need
for stack operations by optimizing register usage.

Original, Non-Optimized Code

In this hypothetical example, we have a sequence of instructions where some
computations could be executed in parallel, but due to their current ordering,
the CPU might experience pipeline stalls.


```asm
.section .text
.globl _start

_start:
    mov $5, %eax             # Load immediate value into %eax
    imul $4, %eax, %ebx      # %ebx = %eax * 4 (Dependent on %eax, potential
stall)

    mov $3, %ecx             # Load immediate value into %ecx
    add %ecx, %ebx           # %ebx += %ecx (Dependent on %ecx and previous
%ebx)

    mov $10, %edx            # Load immediate value into %edx
    sub %eax, %edx           # %edx -= %eax (Dependent on %eax)

    # More operations...
```

Optimized Version with Instruction Scheduling

In the optimized version, we'll rearrange the instructions to better overlap
independent operations and reduce the waiting time for dependent results.

```asm
.section .text
.globl _start

_start:
    mov $5, %eax             # Load immediate value into %eax
    mov $3, %ecx             # Load immediate value into %ecx
    mov $10, %edx            # Load immediate value into %edx

    imul $4, %eax, %ebx      # %ebx = %eax * 4 (No immediate dependency)

    add %ecx, %ebx           # %ebx += %ecx (Independent of the first operation)
    sub %eax, %edx           # %edx -= %eax (No waiting on %eax's previous use)

    # More operations...
```

Explanation of Instruction Scheduling Applied

Parallelizing Independent Operations: By moving the loading of immediate values
(mov $3, %ecx and mov $10, %edx) before their use in arithmetic operations, we
ensure that these values are ready when needed, without waiting for the
completion of %eax's multiplication. This reduces the time CPU spends idle
waiting for dependencies.

Reducing Pipeline Stalls: The reordering ensures that instructions that depend
on the result of previous computations (imul $4, %eax, %ebx and sub %eax, %edx)
are spaced out, allowing the CPU to work on other instructions (mov $3, %ecx
and mov $10, %edx) in the meantime.
