#include <stdio.h>
#include <stdlib.h>

struct String {
  const char *str;
  size_t length;
  void (*concat)(struct String *, struct String *);
  void (*free)(struct String *);
};

size_t s_len(const char *_str) {
  size_t str_len = 0;
  while (_str[str_len] != '\0') {
    str_len++;
  }
  return str_len;
}

void concat_str(struct String *self, struct String *other) {
  size_t new_len = s_len(self->str) + s_len(other->str);
  char *str = (char *)malloc(new_len + 1);
  size_t i = 0;
  while (i < s_len(self->str)) {
    str[i] = self->str[i];
    i++;
  }
  size_t j = 0;
  while (j < s_len(other->str)) {
    str[i + j] = other->str[j];
    j++;
  }
  self->str = str;
  self->length = new_len;
}

void free_str(struct String *self) { free((void *)self->str); }

struct String str_ctor(const char *_str) {
  char *str = (char *)malloc(s_len(_str) + 1);
  size_t i = 0;
  while (i < s_len(_str)) {
    str[i] = _str[i];
    i++;
  }

  struct String s = {str, s_len(_str), concat_str, free_str};
  return s;
}

int main() {
  struct String hello = str_ctor("Hello");
  struct String world = str_ctor(" world ");
  struct String name = str_ctor("takashi!");
  struct String extra = str_ctor(" extra");

  hello.concat(&hello, &world);
  hello.concat(&hello, &name);
  hello.concat(&hello, &extra);

  printf("%s\n", hello.str);
  printf("The string length is: %zu\n", hello.length);

  hello.free(&hello);
  world.free(&world);
  name.free(&name);
  extra.free(&extra);
}
