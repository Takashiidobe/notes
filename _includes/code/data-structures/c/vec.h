#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define auto __auto_type

#define vec_base \
  struct {       \
    size_t cap;  \
    size_t len;  \
  }

#define vec(T)     \
  struct vec_##T { \
    vec_base;      \
    T data[];      \
  }

#define VEC_ALEN(a) (sizeof(a) / sizeof(*a))

#define vec_new(T, xs...)                                                   \
  ({                                                                        \
    const size_t initial_size = 16;                                         \
    const T _xs[]             = {xs};                                       \
    struct vec_##T *v = malloc(sizeof(vec(T)) + sizeof(T) * VEC_ALEN(_xs)); \
    v->cap            = initial_size;                                       \
    v->len            = VEC_ALEN(_xs);                                      \
    for (int i = 0; i < v->len; ++i) v->data[i] = _xs[i];                   \
    v;                                                                      \
  })

#define vec_pop(v) (v->data[--v->len])

#define vec_ref(v, i) (&v->data[i])

#define vec_at(v, i) (*(vec_ref(v, i)))

#define vec_push(v, xs...)                                          \
  ({                                                                \
    const typeof(*v->data) _xs[] = {xs};                            \
    if (v->len + VEC_ALEN(_xs) >= v->cap) {                         \
      while (v->cap <= v->len + VEC_ALEN(_xs)) {                    \
        v->cap = 2 * v->cap;                                        \
      }                                                             \
      v = realloc(v, sizeof(vec_base) + v->cap * sizeof(*v->data)); \
    }                                                               \
    for (int i = 0; i < VEC_ALEN(_xs); ++i) {                       \
      v->data[v->len++] = _xs[i];                                   \
    }                                                               \
    v;                                                              \
  })

#define vec_free(v) free(v)

#define GET_FMT_SPEC(x) \
  _Generic((x), \
    bool: "bool", \
    int: "%d", \
    size_t: "%zu", \
    float: "%f", \
    char: "%c", \
    char *: "%s", \
    const char *: "%s", \
    signed char: "%hhd", \
    unsigned char: "%hhu", \
    signed short: "%hd", \
    unsigned short: "%hu", \
    long long int: "%lld", \
    long double: "%Lf", \
    void *: "%p" \
  )

#define swap(x, y)                 \
  ({                               \
    const typeof(x) _temp = y;     \
    y                     = x;     \
    x                     = _temp; \
  })

#define vec_print(v)                                                \
  ({                                                                \
    _Pragma("GCC diagnostic push");                                 \
    _Pragma("GCC diagnostic ignored \"-Wformat-extra-args\"");      \
    printf("[");                                                    \
    for (int i = 0; i < v->len; ++i) {                              \
      bool is_bool = strcmp(GET_FMT_SPEC(v->data[i]), "bool") == 0; \
      is_bool ? printf((bool)v->data[i] ? "true" : "false")         \
              : printf(GET_FMT_SPEC(v->data[i]), v->data[i]);       \
      if (i + 1 < v->len) printf(", ");                             \
    }                                                               \
    printf("]\n");                                                  \
    _Pragma("GCC diagnostic pop");                                  \
  })

static inline void _vec_free(void **vec) { free(*vec); }

#define vec_raii __attribute__((cleanup(_vec_free)))
