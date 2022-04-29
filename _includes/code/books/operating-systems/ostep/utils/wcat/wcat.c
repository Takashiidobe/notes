#include <stdio.h>
#include <stdlib.h>

const size_t BUF_SIZE = 80;

int main(int argc, char *argv[]) {
  if (argc < 1) {
    return EXIT_FAILURE;
    exit(1);
  }

  char str[BUF_SIZE];
  for (size_t file = 1; file < argc; file++) {
    FILE *fp = fopen(argv[file], "r");

    if (fp == NULL) {
      printf("wcat: cannot open file\n");
      exit(1);
    }

    while (fgets(str, BUF_SIZE, fp) != NULL) {
      printf("%s", str);
    }

    fclose(fp);
  }
}
