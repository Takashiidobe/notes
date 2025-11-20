---
title: lock-based-concurrent-data-structures
---
# Lock-based Concurrent Data Structures

Prev: [[15-locks]]
Next: [[17-condition-variables]]





## Concurrent Counters

The first data structure is a counter. A first attempt is simple but
inefficient, it doesn't use multi-threading:

```c
typedef struct __counter_t {
  int value;
} counter_t;
void init(counter_t *c) { c->value = 0; }
void increment(counter_t *c) { c->value++; }
void decrement(counter_t *c) { c->value--; }
int get(counter_t *c) { return c->value; }
```

Next, we add a single lock that we acquire for all operations:

```c
typedef struct __counter_t {
  int value;
  pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
  c->value = 0;
  Pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
  Pthread_mutex_lock(&c->lock);
  c->value++;
  Pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
  Pthread_mutex_lock(&c->lock);
  c->value--;
  Pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
  Pthread_mutex_lock(&c->lock);
  int rc = c->value;
  Pthread_mutex_unlock(&c->lock);
  return rc;
}
```

This is now thread-safe, but performs worse than the single-threaded
example due to lock overhead.

## Approximate Counter Implementation

We can do better by allowing stale reads. Instead of synchronizing on
every operation, we have a set of local counters, which are then
synchronized to the global counter every once in a while.

```c
typedef struct __counter_t {
  int global;                     // global count
  pthread_mutex_t glock;          // global lock
  int local[NUMCPUS];             // per-CPU count
  pthread_mutex_t llock[NUMCPUS]; // ... and locks
  int threshold;                  // update frequency
} counter_t;

// init: record threshold, init locks, init values
// of all local counts and global count
void init(counter_t *c, int threshold) {
  c->threshold = threshold;
  c->global = 0;
  pthread_mutex_init(&c->glock, NULL);
  int i;
  for (i = 0; i < NUMCPUS; i++) {
    c->local[i] = 0;
    pthread_mutex_init(&c->llock[i], NULL);
  }
}

// update: usually, just grab local lock and update
// local amount; once local count has risen ’threshold’,
// grab global lock and transfer local values to it
void update(counter_t *c, int threadID, int amt) {
  int cpu = threadID % NUMCPUS;
  pthread_mutex_lock(&c->llock[cpu]);
  c->local[cpu] += amt;
  if (c->local[cpu] >= c->threshold) {
    // transfer to global (assumes amt>0)
    pthread_mutex_lock(&c->glock);
    c->global += c->local[cpu];
    pthread_mutex_unlock(&c->glock);
    c->local[cpu] = 0;
  }
  pthread_mutex_unlock(&c->llock[cpu]);
}

// get: just return global amount (approximate)
int get(counter_t *c) {
  pthread_mutex_lock(&c->glock);
  int val = c->global;
  pthread_mutex_unlock(&c->glock);
  return val; // only approximate!
}
```

This performs much better -- having much higher performance (at the cost
of accuracy). If we can say that reads are much less often, but require
accuracy, they can synchronize between all locks and sacrifice
performance for accuracy.

## Concurrent Linked Lists

Concurrency can be added to linked lists by adding a lock for inserts
and lookups:

```c
void List_Init(list_t *L) {
  L->head = NULL;
  pthread_mutex_init(&L->lock, NULL);
}

void List_Insert(list_t *L, int key) {
  // synchronization not needed
  node_t *new = malloc(sizeof(node_t));
  if (new == NULL) {
    perror("malloc");
    return;
  }
  new->key = key;

  // just lock critical section
  pthread_mutex_lock(&L->lock);
  new->next = L->head;
  L->head = new;
  pthread_mutex_unlock(&L->lock);
}

int List_Lookup(list_t *L, int key) {
  int rv = -1;
  pthread_mutex_lock(&L->lock);
  node_t *curr = L->head;
  while (curr) {
    if (curr->key == key) {
      rv = 0;
      break;
    }
    curr = curr->next;
  }
  pthread_mutex_unlock(&L->lock);
  return rv; // now both success and failure
}
```

This list doesn't scale. Instead, we can do
`hand-over-hand-locking`, where every node has a lock. This makes
operations like inserts faster, but having to traverse the list incurs
the overhead of locking, which makes this approach slow.

## Concurrent Queues

For a concurrent queue, this implementation uses a dummy node and a lock
on the head and tail for operations:

```c
typedef struct __node_t {
  int value;
  struct __node_t *next;
} node_t;

typedef struct __queue_t {
  node_t *head;
  node_t *tail;
  pthread_mutex_t head_lock, tail_lock;
}

 void Queue_Init(queue_t *q) {
  node_t *tmp = malloc(sizeof(node_t));
  tmp->next = NULL;
  q->head = q->tail = tmp;
  pthread_mutex_init(&q->head_lock, NULL);
  pthread_mutex_init(&q->tail_lock, NULL);
}

void Queue_Enqueue(queue_t *q, int value) {
  node_t *tmp = malloc(sizeof(node_t));
  assert(tmp != NULL);
  tmp->value = value;
  tmp->next = NULL;

  pthread_mutex_lock(&q->tail_lock);
  q->tail->next = tmp;
  q->tail = tmp;
  pthread_mutex_unlock(&q->tail_lock);
}

int Queue_Dequeue(queue_t *q, int *value) {
  pthread_mutex_lock(&q->head_lock);
  node_t *tmp = q->head;
  node_t *new_head = tmp->next;
  if (new_head == NULL) {
    pthread_mutex_unlock(&q->head_lock);
    return -1; // queue was empty
  }
  *value = new_head->value;
  q->head = new_head;
  pthread_mutex_unlock(&q->head_lock);
  free(tmp);
  return 0;
}
```

There are also faster concurrent queues using hazard pointers and
Compare-and-Swap routines. To enqueue to a queue with Compare-and-swap,
the data structure tries to enqueue a node with compare-and-swap. If it
succeeds, great. If it fails, it retries after re-reading the current
tail node. If it doesn't succeed, it may try to yield or apply another
strategy.

## Concurrent hash Table

A concurrent hashtable uses separate chaining and the concurrent lists
from before. This uses a lock per hash bucket, so the data structure
only has to lock parts of itself based on an access or not.

```c
#define BUCKETS (101)

typedef struct __hash_t {
  list_t lists[BUCKETS];
} hash_t;

void Hash_Init(hash_t *H) {
  int i;
  for (i = 0; i < BUCKETS; i++)
    List_Init(&H->lists[i]);
}

int Hash_Insert(hash_t *H, int key) {
  return List_Insert(&H->lists[key % BUCKETS], key);
}

int Hash_Lookup(hash_t *H, int key) {
  return List_Lookup(&H->lists[key % BUCKETS], key);
}
```

Prev: [[15-locks]]
Next: [[17-condition-variables]]
