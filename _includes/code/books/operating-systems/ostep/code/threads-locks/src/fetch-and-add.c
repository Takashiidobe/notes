#include <stdio.h>
#include <stdatomic.h>

volatile int balance = 0;

typedef struct __lock_t {
  int status;
} lock_t;

// With a hardware instruction for compare and swap, this now doesn't spin forever as long as we can preempt threads
void lock(lock_t *mtx) {
  while (__sync_bool_compare_and_swap(&mtx->status, 0, 1) == 1);
  mtx->status = 1;
}

int unlock(lock_t *mutex) {
  mutex->status = 0;

  return 1;
}

void init(lock_t *mutex) {
  mutex->status = 0;
}

int fetch_and_add(int *ptr) {
  int old = *ptr;
  *ptr = old + 1;
  return old;
}

// with GCC builtins
int fetch_and_inc(int *ptr) {
  return __atomic_fetch_add(ptr, 1, __ATOMIC_SEQ_CST);
}


int main() {
  lock_t mutex;
  init(&mutex);
  lock(&mutex);
  printf("Locking mutex\n");
  lock(&mutex);
  printf("Locking mutex\n");
  unlock(&mutex);
  printf("Unlocking mutex\n");
  unlock(&mutex);
  printf("Unlocking mutex\n");
}
