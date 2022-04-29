#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compress_and_print_line(char* buf) {
  size_t i = 0;
  size_t j = 1;
  size_t buf_len = strlen(buf);
  size_t count = 1;
  while (j < buf_len) {
    if (buf[i] != buf[j]) {
      if (count > 1) {
        printf("%zu%c", count, buf[i]);
      } else {
        printf("%c", buf[i]);
      }
      i++;
      j++;
      count = 1;
    } else {
      while (buf[i] == buf[j]) {
        count++;
        i++;
        j++;
      }
    }
  }
  printf("\n");
}

int main(int argc, char* argv[]) {
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  FILE *fp = fopen(argv[1], "r");

  if (!fp) {
    printf("wzip: cannot open file\n");
    return EXIT_FAILURE;
  }

  while (getline(&line_buf, &line_buf_size, fp) >= 0) {
    compress_and_print_line(line_buf);
  }

  free(line_buf);
  line_buf = NULL;

  fclose(fp);

  return EXIT_SUCCESS;
}

