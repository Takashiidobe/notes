#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define tuple(F, S)                                                            \
  struct tuple_##F_##S {                                                       \
    F first;                                                                   \
    S second;                                                                  \
    bool first_set;                                                            \
    bool second_set;                                                           \
  }

#define auto __auto_type

void tuple_free(void *t) { free(t); }

void _tuple_free(void **t) { free(*t); }

#define tuple_raii __attribute__((cleanup(_tuple_free)))

#define tuple_empty_new(F, S)                                                  \
  ({                                                                           \
    struct tuple_##F_##S *t = malloc(sizeof(tuple(F, S)));                     \
    t->first_set = false;                                                      \
    t->second_set = false;                                                     \
    t;                                                                         \
  })

#define tuple_new(F, S, f, s)                                                  \
  ({                                                                           \
    struct tuple_##F_##S *t = malloc(sizeof(tuple(F, S)));                     \
    t->first = f;                                                              \
    t->second = s;                                                             \
    t->first_set = true;                                                       \
    t->second_set = true;                                                      \
    t;                                                                         \
  })

#define first(t) ({ t->first_set ? t->first : 0; })
#define second(t) ({ t->second_set ? t->second : 0; })

#define can_get_first(t) ({ t->first_set == true; })
#define can_get_second(t) ({ t->second_set == true; })

#define tuple_at(t, i)                                                         \
  ({ can_get_first(t) ? first(t) : can_get_second(t) ? second(t) : 0; })

#define tuple_set(t, i, val)                                                   \
  ({                                                                           \
    if (t->first_set == false && i == 0) {                                     \
      t->first = val;                                                          \
      t->first_set = true;                                                     \
    } else if (t->second_set == false && i == 1) {                             \
      t->second = val;                                                         \
      t->second_set = true;                                                    \
    } else                                                                     \
      0;                                                                       \
  })

#define GET_FMT_SPEC(x)                                                        \
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

#define tuple_print(t)                                                         \
  ({                                                                           \
    _Pragma("GCC diagnostic push");                                            \
    _Pragma("GCC diagnostic ignored \"-Wformat-extra-args\"");                 \
    printf("(");                                                               \
    bool is_first_bool = strcmp(GET_FMT_SPEC(t->first), "bool") == 0;          \
    is_first_bool ? printf((bool)t->first ? "true" : "false")                  \
                  : printf(GET_FMT_SPEC(t->first), t->first);                  \
    printf(", ");                                                              \
    bool is_second_bool = strcmp(GET_FMT_SPEC(t->second), "bool") == 0;        \
    is_second_bool ? printf((bool)t->second ? "true" : "false")                \
                   : printf(GET_FMT_SPEC(t->second), t->second);               \
    printf(")\n");                                                             \
    _Pragma("GCC diagnostic pop");                                             \
  })
