#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *_calloc(size_t n, size_t size) {
  void *result = malloc(n * size);

  if (result != NULL) {
    memset(result, 0x00, n * size);
  }

  return result;
}

int main() {
  int *nums = _calloc(4, 10);
  for (int i = 0; i < 10; i++)
    nums[i] = (i + 1) * 10;

  for (int i = 0; i < 10; i++)
    printf("%d\n", nums[i]);

  free(nums);
  return 0;
}
