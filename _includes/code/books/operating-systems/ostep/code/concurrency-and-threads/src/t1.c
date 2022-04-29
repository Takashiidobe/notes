#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include "../../include/common.h"
#include "../../include/common_threads.h"

// this makes the program 10x slower
// hyperfine './build/t1'                                                                                                                                 Tue Apr 26 19:46:43 2022
// Benchmark #1: ./build/t1
//   Time (mean ± σ):     266.2 ms ±  18.4 ms    [User: 522.4 ms, System: 1.9 ms]
//   Range (min … max):   227.0 ms … 284.4 ms    11 runs
atomic_int counter = 0;

// hyperfine './build/t1'                                                                                                                         196ms  Tue Apr 26 19:47:06 2022
// Benchmark #1: ./build/t1
//  Time (mean ± σ):      25.8 ms ±   1.5 ms    [User: 46.5 ms, System: 0.9 ms]
//  Range (min … max):    23.9 ms …  30.3 ms    98 runs
// volatile int counter = 0;

void *mythread(void *arg) {
  printf("%s: begin\n", (char *) arg);
  for (int i = 0; i < 1e7; i++) {
    counter++;
  }
  printf("%s: done\n", (char *) arg);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t p1, p2;
  printf("main: begin (counter = %d)\n", counter);
  Pthread_create(&p1, NULL, mythread, "A");
  Pthread_create(&p2, NULL, mythread, "B");

  // join waits for the threads to finish
  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);
  printf("main: done with both (counter = %d)\n", counter);
  return 0;
}
