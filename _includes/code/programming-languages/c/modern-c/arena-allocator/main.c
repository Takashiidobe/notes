#include <stdio.h>
#include <stdlib.h>

typedef struct allocator_t {
  void *memory;
  size_t size;
} allocator_t;

allocator_t *make_allocator(size_t s) {
  allocator_t *alloc = malloc(sizeof(s) + s);

  alloc->size = s;
  alloc->memory = malloc(sizeof(s));

  return alloc;
}

void free_allocator(void *alloc) { free(alloc); }

int main() {
  size_t size = 80000;
  allocator_t *temp_allocator = make_allocator(size);

  int game_is_running = 1;

  while (game_is_running) {
    // do work
    // request memory from memory allocator when needed.

    free_allocator(temp_allocator);
  }
}
