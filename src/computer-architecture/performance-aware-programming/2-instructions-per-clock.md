---
title: 2-instructions-per-clock
date created: Saturday, March 1st 2025, 8:32:38 pm
date modified: Sunday, March 2nd 2025, 8:34:44 am
---

In the discussion about waste, there was discussion about only running what you needed for what you're trying to do.

The C version produced 0.8 adds per second.

But looking at the loop again:

There are four things that need to happen:
1. `i` is checked to be less than `count`
2. `input[i]` is loaded
3. `input[i]` is added to sum
4. i is incremented.

```c
for (int i = 0; i < count; i++)
	sum += input[i]
```

So we should theoretically have at max 0.25 instructions per clock. A chip is capable of doing a certain number of instructions at the same time, so we can assume that since there were ~0.8 adds per clock with this naive code, and there are actually 4 instructions going on, there are ~3.2 IPC.

This post discusses unrolling a loop, but that's something a compiler can do for us anyway.

But it focuses on finding the bottleneck to optimizing parallelism, which is that `sum` is both a source and destination for the add. So, we can break it by doing it in parallel for the compiler by breaking up the add into four parts:

```c
typedef unsigned int u32;
u32 QuadScalar(u32 Count, u32 *Input)
{
    u32 SumA = 0;
    u32 SumB = 0;
    u32 SumC = 0;
    u32 SumD = 0;
    for(u32 Index = 0; Index < Count; Index += 4)
    {
        SumA += Input[Index + 0];
        SumB += Input[Index + 1];
        SumC += Input[Index + 2];
        SumD += Input[Index + 3];
    }
    
    u32 Sum = SumA + SumB + SumC + SumD;
    return Sum;
}
```

This about doubles the throughput to 1.8 IPC.

Zen 5 chips (the current AMD Ryzens have about 8 IPC, so this could potentially run even faster.)