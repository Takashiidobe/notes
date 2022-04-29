#include <stdio.h>
#include <pthread.h>
#include "../../include/common_threads.h"

int main() {
  volatile int balance = 0;

  pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
  Pthread_mutex_lock(&lock);
  balance = balance + 1;
  printf("%d\n", balance);
  Pthread_mutex_unlock(&lock);
}

