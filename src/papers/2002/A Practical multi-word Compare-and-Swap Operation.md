---
pdf_url: "[[A Practical multi-word Compare-and-Swap Operation]]"
title: A Practical Multi-Word Compare and Swap Operation
author:
  - Ian A. Pratt
  - Keir Fraser
  - Timothy L. Harris
date created: Sunday, July 20th 2025, 10:25:43 am
date modified: Sunday, July 20th 2025, 10:28:16 am
---

# A Practical Multi-Word Compare and Swap Operation

This paper introduces the RDCSS (Restricted double compare and single
swap) concurrent instruction using CAS (compare and swap).

This RDCSS instruction is then used to write MWCAS (Multi-word compare
and swap).

## RDCSS

RDCSS checks to make sure that two locations are set to the correct
value provided (i.e. no other thread has mutated them) and then updates
the second memory location to a value provided.

We could try something like this, but this isn't thread-safe (between
the first line of the function and the second, something could've
updated `*a2`, so this function is not linearizable.

```c
uint64_t RDCSS(uint64_t *a1, uint64_t *a2, uint64_t o1, uint64_t o2, uint64_t n2) {
  uint64_t a2_local = *a2;
  if(*a1 == o1 && a2_local == o2) *a2 = n2;
  return a2_local;
}
```

We can reduce this algorithm to 2PL (2 Phase Locking) like so:

```c
uint64_t RDCSS(uint64_t *a1, uint64_t *a2, uint64_t o1, uint64_t o2, uint64_t n2) {
  lock(a2);
  uint64_t a2_local = *a2;  // Access protected by lock on a2
  lock(a1);
  uint64_t a1_local = *a1;  // Access protected by lock on a1
  unlock(a1);
  if (a1_local == o1 && a2_local == o2) *a2 = n2; // Protected by lock on a2
  unlock(a2);
  return a2_local;
}
```

Unfortunately, this requires locking `a2` and `a1`, so it's not correct
either.

The paper sidesteps this in two ways: having a cooperative approach, and
using descriptors.

If other threads notice that an address has a descriptor on it, and the
thread did not place that descriptor in that memory address, they wait
until the other thread is done with its work before continuing on.

This looks like this:

```c
struct RDCSSDescriptor_t {
    word_t* a1;        // control address
    const word_t  o1;  // expected control value
    word_t* a2;        // data address
    const word_t  o2;  // expected data value
    const word_t  n2;  // new data value
};

word_t RDCSS(RDCSSDescriptor_t* d) {
    do {
        r = CAS1(d->a2, d->o2, d);
        if (IsDescriptor(r)) Complete(r);   // H1
    } while (IsDescriptor(r));
    if (r == d->o2) Complete(d);
    return r;
}

word_t RDCSSRead(addr_t *addr) {
    do {
        r = __atomic_load(addr);
        if (IsDescriptor(r)) Complete(r);
    } while (IsDescriptor(r));
    return r;
}

void Complete(RDCSSDescriptor_t* d) {
    v = __atomic_load(d->a1);
    if (v == d->o1) CAS1(d->a2, d, d->n2);
    else CAS1(d->a2, d, d->o2);
}
```

## Implementing Multi-word Compare and Swap

Now, we can implement multi-word compare and swap, which looks like 2PL
(try to install descriptors into both memory addresses using RDCSS. If
both operations succeed, we write the values to both, since we know this
is race-free (since other threads will know to wait, since our
descriptors are still there).

If either or both operations fail, the operation is marked as failed,
and retried.

```c
struct CASNDescriptor_t {
    const int n;        // Number of words we are updating
    Status status;      // Status of overall operation
    Entry entry[];      // Array of entries with `addr`, `old_val`, `new_val`
}

bool CASN(CASNDescriptor_t* cd) {
    if (__atomic_load(&(cd->status)) == UNDECIDED) {
        // phase1: Install the descriptors
        status = SUCCEEDED;
        for (i = 0; (i < cd->n) && (status == SUCCEEDED); i++) {
retry_entry:
            entry = cd->entry[i];
            val = RDCSS(new RDCSSDescriptor_t(  // X1
                                &(cd->status), UNDECIDED, entry.addr,
                                entry.old_val, cd));
            if (IsCASNDescriptor(val)) {
                if (val != cd) {
                    CASN(val);
                    goto retry_entry;
                }  // else we installed descriptor successfully.
            } else if (val != entry.old_val) {
                status = FAILED;
            }
        }
        CAS1(&(cd->status), UNDECIDED, status);  // C4: Update status
    }
    // phase2: Roll forward/back the descriptors to values.
    succeeded = (__atomic_load(&(cd->status)) == SUCCEEDED);
    for (i = 0; i < cd->n; i++)
        CAS1(cd->entry[i].addr, cd,
             succeeded ? (cd->entry[i].new_val) : (cd->entry[i].old_val));
    return succeeded;
}

word_t CASNRead(addr_t *addr) {
    do {
        r = RDCSSRead(addr);
        if (IsCASNDescriptor(r)) CASN(r);
    } while (IsCASNDescriptor(r));
    return r;
}
```

## Performance

Shockingly, according to the paper, the algorithm performs roughly as
well as the lock version, even though this algorithm is lock-free.