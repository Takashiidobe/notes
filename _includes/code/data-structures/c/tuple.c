#include "tuple.h"

#include <stdio.h>

typedef const char *string;

tuple(string, bool);

int main() {
  auto *t = tuple_new(size_t, size_t, 10, 20);
  auto *t1 = tuple_new(string, string, "hello", "world");
  auto *t2 = tuple_new(uint8_t, uint8_t, 1, 1);
  auto *t3 = tuple_empty_new(size_t, size_t);
  auto *t4 = tuple_new(string, bool, "string", false);
  auto *t5 = tuple_new(uint8_t, uint8_t, 1, 0);
  auto *t6 = tuple_new(bool, string, true, "string");
  tuple_set(t, 0, 10);
  tuple_set(t, 1, 20);
  tuple_set(t1, 0, "changed");
  tuple_set(t1, 1, "changed");
  tuple_set(t2, 0, 10);
  tuple_set(t2, 1, 30);
  tuple_set(t3, 0, 1000);
  tuple_set(t3, 1, 2000);
  tuple_print(t);
  tuple_print(t1);
  tuple_print(t2);
  tuple_print(t3);
  tuple_print(t4);
  tuple_print(t5);
  tuple_print(t6);
  tuple_free(t);
  tuple_free(t1);
  tuple_free(t2);
  tuple_free(t3);
  tuple_free(t4);
  tuple_free(t5);
  tuple_free(t6);
}
