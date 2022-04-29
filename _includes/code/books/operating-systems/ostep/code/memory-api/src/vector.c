#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
  size_t len;
  size_t capacity;
  int *items;
} Vector;

Vector *vector_new(const size_t len, ...);

void vector_free(Vector *v);

int vector_get(Vector *v, size_t index);

void vector_set(Vector *v, size_t index, int val);

int vector_empty(Vector *v);

void vector_push(Vector *v, int val);

int *vector_begin(Vector *v);

int *vector_end(Vector *v);

int *vector_next(Vector *v, int *it);

void vector_for_each(Vector *v, int (*fn)(int));

int vector_pop(Vector *v);


size_t max(size_t a, size_t b) {
  return a > b ? a : b;
}

Vector *vector_new(const size_t len, ...) {
  Vector *v = malloc(sizeof(Vector));
  int capacity = 8;
  capacity = max(pow(2, ceil(log(len) / log(2))), capacity);

  v->items = malloc(sizeof(int) * capacity);
  v->len = len;
  v->capacity = capacity;

  if (len > 0) {
    va_list argp;
    va_start(argp, len);

    for (size_t i = 0; i < len; i++) {
      v->items[i] = va_arg(argp, int);
    }

    va_end(argp);
  }

  return v;
}

Vector *vector_copy(const Vector *v) {
  Vector *copy = malloc(sizeof(Vector));
  copy->items = malloc(sizeof(int) * v->len);
  copy->capacity = v->capacity;
  copy->len = v->len;

  for (size_t i = 0; i < v->len; i++)
    copy->items[i] = v->items[i];

  return copy;
}

void vector_free(Vector *v) {
  free(v->items);
  free(v);
}

int vector_get(Vector *v, size_t index) {
  assert(index >= 0 && index < v->len);
  return v->items[index];
}

void vector_set(Vector *v, size_t index, int val) {
  assert(index >= 0 && index < v->len);
  v->items[index] = val;
}

int vector_empty(Vector *v) { return v->len == 0; }

void vector_push(Vector *v, int val) {
  if (v->len == v->capacity) {
    v->capacity *= 2;
    v->items = realloc(v->items, sizeof(int) * v->capacity);
  }
  v->items[v->len] = val;
  v->len++;
}

int *vector_begin(Vector *v) { return &v->items[0]; }

int *vector_end(Vector *v) { return &v->items[v->len]; }

int *vector_next(Vector *v, int *it) {
  if (it != vector_end(v))
    return ++it;
  return NULL;
}

void vector_for_each(Vector *v, int (*fn)(int)) {
  for (int i = 0; i < v->len; i++) {
    v->items[i] = (*fn)(v->items[i]);
  }
}

int vector_peek(Vector *v) { return v->items[v->len - 1]; }

int vector_pop(Vector *v) {
  assert(v->len > 0);
  int top = vector_peek(v);
  v->len--;
  return top;
}

int main(void) {
  Vector* v = vector_new(8, 0, 1, 2, 3, 4, 5, 6, 7);

  printf("begin: %d\n", *vector_begin(v));

  for (int* it = vector_begin(v); it != vector_end(v); ++it) {
    printf("%d ", *it);
  }

  puts("");

  int* it = vector_begin(v);
  int* end = vector_end(v);
  while (it != end) {
    printf("%d ", *it);
    it = vector_next(v, it);
  }

  vector_free(v);
}

