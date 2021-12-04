#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef enum valid_t {
  FULL_READ,
  INCOMPLETE,
  COULD_NOT_OPEN,
  READ_FAILED,
  CLOSE_FAILED
} valid_t;

typedef struct file_contents_t {
  char *data;
  size_t size;
  valid_t valid;
} file_contents_t;

file_contents_t read_file(const char *name) {
  file_contents_t result = {};

  FILE *f = fopen(name, "r");
  char c;
  size_t i = 0;

  char buf[8024];

  if (f == NULL) {
    result.valid = COULD_NOT_OPEN;
    return result;
  }

  while ((c = fgetc(f)) != EOF) {
    buf[i] = c;
    i++;
  }

  buf[i - 1] = '\0';

  result.size = i + 1;
  result.data = buf;

  if (fclose(f) == EOF) {
    result.valid = CLOSE_FAILED;
    return result;
  }

  return result;
}

void print_file_t(file_contents_t f) {
  char str[8024];
  char starting[800];
  sprintf(starting, "[data: %s, size: %zu, ", f.data, f.size);

  strcpy(str, starting);

  switch (f.valid) {
  case FULL_READ:
    strcat(str, "message: FULL_READ");
    break;
  case INCOMPLETE:
    strcat(str, "message: INCOMPLETE");
    break;
  case COULD_NOT_OPEN:
    strcat(str, "message: COULD_NOT_OPEN");
    break;
  case READ_FAILED:
    strcat(str, "message: READ_FAILED");
    break;
  case CLOSE_FAILED:
    strcat(str, "message: CLOSE_FAILED");
    break;
  }

  strcat(str, "]\n");

  printf("%s", str);
}

int main() {
  file_contents_t f = read_file("test.txt");
  print_file_t(f);
}
