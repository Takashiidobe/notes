#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t MAX_SIZE = 1024;

struct Result {
  int valid;
  size_t location;
};

void computeLPSarray(char *pat, int M, int *lps) {
  int len = 0;
  int i;

  lps[0] = 0;
  i = 1;

  while(i <  M) {
    if (pat[i] == pat[len]) {
      lps[i++] = len++;
    } else if (len != 0) {
      len = lps[len - 1];
    } else {
      lps[i++] = 0;
    }
  }
}

void KMPSearch(char *pat, char *txt, struct Result *result) {
  int M = strlen(pat);
  int N = strlen(txt);

  int lps[MAX_SIZE];
  memset(lps, 0, 0);

  if (M > MAX_SIZE) {
    exit(1);
  }

  computeLPSarray(pat, M, lps);

  int i = 0;
  int j = 0;
  while (i < N) {
    if (pat[j] == txt[i]) {
      j++;
      i++;
    }
    if (j == M) {
      result->valid = 1;
      result->location = i - j;
      return;
    }
    else if(pat[j] != txt[i]) {
      if (j != 0)
        j = lps[j - 1];
      else
        i++;
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    return EXIT_FAILURE;
  }

  struct Result result;

  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  ssize_t line_size;
  FILE *fp = fopen(argv[2], "r");

  if (!fp) {
    printf("wgrep: cannot open file\n");
    return EXIT_FAILURE;
  }

  line_size = getline(&line_buf, &line_buf_size, fp);

  while (line_size >= 0) {
    result.valid = 0;
    line_count++;

    KMPSearch(argv[1], line_buf, &result);

    if (result.valid) {
      printf("%s", line_buf);
    }

    line_size = getline(&line_buf, &line_buf_size, fp);
  }

  free(line_buf);
  line_buf = NULL;

  fclose(fp);

  return EXIT_SUCCESS;
}
