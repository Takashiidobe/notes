#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

uint8_t parse_digit(char c) {
  return c - '0';
}

void decompress_and_print_line(char* buf) {
  size_t buf_len = strlen(buf);
  int curr_num = 1;
  for (int i = 0; i < buf_len; i++) {
    if (isdigit(buf[i])) {
      if (curr_num == 1) {
        curr_num = parse_digit(buf[i]);
      } else {
        curr_num *= 10 + parse_digit(buf[i]);
      }
    } else {
      for (int j = 0; j < curr_num; j++) {
        printf("%c", buf[i]);
      }
      curr_num = 1;
    }
  }
}

int main(int argc, char* argv[]) {
  char *line_buf = NULL;
  FILE *fp = fopen(argv[1], "r");
  size_t line_buf_size = 0;

  if (!fp) {
    printf("wzip: cannot open file\n");
    return EXIT_FAILURE;
  }

  while (getline(&line_buf, &line_buf_size, fp) >= 0) {
    decompress_and_print_line(line_buf);
  }

  free(line_buf);
  line_buf = NULL;

  fclose(fp);

  return EXIT_SUCCESS;
}

