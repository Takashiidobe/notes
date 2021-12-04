#include <stdio.h>
#include <stdlib.h>

const size_t STARTING_CAPACITY = 8;
struct Array {
  int *items;
  size_t length;
  size_t capacity;
  void (*push)(struct Array *, int);
  int (*pop)(struct Array *);
  void (*print)(struct Array *);
  void (*free)(struct Array *);
};

void push_back(struct Array *self, int _value) {
  if (self->capacity == self->length) {
    int placeholder[self->capacity * 2];

    for (size_t i = 0; i < self->length; i++) {
      placeholder[i] = self->items[i];
    }

    realloc(self->items, sizeof(self->items) * 2);

    for (size_t i = 0; i < self->capacity; i++) {
      self->items[i] = placeholder[i];
    }

    self->capacity *= 2;
  }
  self->items[self->length] = _value;
  self->length++;
}

int pop_back(struct Array *self) {
  if (self->capacity > self->length * 3) {
    int placeholder[self->capacity / 3];
    for (size_t i = 0; i < self->length; i++) {
      placeholder[i] = self->items[i];
    }

    size_t result = realloc(self->items, sizeof(self->items) * 2);

    for (size_t i = 0; i < self->capacity; i++) {
      self->items[i] = placeholder[i];
    }

    self->capacity /= 3;
  }
  int value = self->items[self->length - 1];
  self->length--;
  return value;
}

void print_array(struct Array *self) {
  for (size_t i = 0; i < self->length; i++) {
    printf("%d\n", self->items[i]);
  }
}

void free_array(struct Array *self) { free(self->items); }

struct Array array_ctor() {
  struct Array a = {(int *)malloc(sizeof(int) * STARTING_CAPACITY),
                    0,
                    STARTING_CAPACITY,
                    push_back,
                    pop_back,
                    print_array,
                    free_array};
  return a;
}

int main() {
  struct Array a = array_ctor();
  for (int i = 1; i <= 65; i++) {
    a.push(&a, i);
  }
  a.print(&a);
  printf("The length of the array is: %zu\n", a.length);
  printf("The capacity of the array is: %zu\n", a.capacity);
  for (int i = 1; i <= 32; i++) {
    a.pop(&a);
  }
  a.print(&a);
  printf("The length of the array is: %zu\n", a.length);
  printf("The capacity of the array is: %zu\n", a.capacity);
  a.free(&a);
}
