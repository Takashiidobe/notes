#include <stdio.h>
#include <stdlib.h>

int main() {
  int* data = malloc(sizeof(int) * 100);
  data[100] = 0; // program is incorrect, writing past its buffer.

}
