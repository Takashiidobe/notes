#include <stdio.h>

volatile int balance = 0;

typedef struct __lock_t {
  int status;
} lock_t;

void lock(lock_t *mtx) {
  while (mtx->status == 1);
  mtx->status = 1;
}

int unlock(lock_t *mutex) {
  mutex->status = 0;

  return 1;
}

void init(lock_t *mutex) {
  mutex->status = 0;
}

// this is slow and error prone (spin-waiting is a waste of time, and prone to deadlock (if two leases are given out)).

int main() {
  lock_t mutex;
  init(&mutex);
  lock(&mutex);
  printf("Inside mutex\n");
  unlock(&mutex);
  printf("Outside mutex\n");
}
