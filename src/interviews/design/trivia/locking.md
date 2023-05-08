# Locking

Locking prevents code from accessing a critical section. This is required, because if two threads update the same data concurrently without synchronization, data corruption can occur.

## Read-Copy-Update

Read-Copy-Update is a reader favored way of allowing both readers and writers.

All readers are never blocked, while writers make a copy of the data structure, make their update, and atomically swap their copy into the old pointer. This means some reads will be stale (they started reading the data structure, then pointers swapped, then the read completed), but readers don't block each other, and neither do writers.

## Left-Right

Left-Right makes two copies of a data structure:

Readers read one copy of the data structure, which isn't allowed to be mutated. Writers write to another copy of the data structure, which requires a mutex to do. At some point (an epoch), the readers are drained out, and the two copies swap, so readers see updated values, and then updates are applied to the old reader copy. Finally, the writers can update the new copy.

Thus, readers are never blocked, but it might take a bit of time for writers to get to update, due to contending for the lock + waiting for updates to complete.

## Seqlock

Seq-lock solves the same problem in a different way.

Seq locks consist of a mutex and an atomic int.
Writers acquire the mutex, and increment the atomic int, do the mutation, then increment the atomic int, and then release the mutex.

Readers don't have to acquire a mutex at all, but they atomically read the int's value, then they read the data, then they read the int's value again. If the atomic int's value has changed, then the underlying data has changed, so they retry. Otherwise, their read is consistent and up-to-date, so they succeed here.

## Spinlocks

Spinlocking (or blocking) means a thread waits until a certain condition is met, wasting CPU cycles. This avoids a context switch (which can take 10 microseconds - 1+ milliseconds), so this can be preferred in some situations to setting the thread to sleep.

## CondVars

Condvars are variables that allow a thread to sleep and be woken up when a certain condition has been met.

## Monitors

Monitors consist of a mutex and a condvar, and guards a critical section (like a mutex). One thread is allowed in after acquiring the mutex, where the thread may choose to signal for another thread to come into the critical section and put itself to sleep, or exit the critical section and signal for another thread to take its place.

## Reader-Writer locks

Reader-writer locks allow infinite readers or one writer to be in a critical section at one time. They could consist of a semaphore to monitor the readers, and a mutex + condvar for writers.

Readers increment the semaphore on entry of the critical section and decrement it on exit.

Writers have to acquire both the mutex and make sure that the semaphore has a count of 0.

Thus, readers can starve out writers. To make this fair, readers can replace their semaphore with a latch, which would block readers when a writer needs to go in, allowing writers to take their turn, but this would block readers while the mutation takes place.

## Semaphores

Semaphores count the number of concurrent threads are accessing a critical section. They can be used for signaling.

## Mutexes

Mutexes only allow one concurrent thread to access a critical section.

## Barriers

Barriers are reusable latches that allow threads to accessing a critical section concurrently after a certain number of them have reached the waiting point, then they can all enter the critical section concurrently.

## Latches

Latches are a synchronization method that collects a certain number of threads to do a task, and when that number if met, allows them to enter the concurrent area all at once.

## Memory Fences

Memory fences force synchronization of atomic and non-atomic instructions at the point the fence is set up.

## Memory Reordering

## Compare and Swap

## Copy on Write

## Hazard Pointers and the ABA problem

## Memory Ordering

Relaxed

Consume

Acquire

release

acq_rel

seq_cst
