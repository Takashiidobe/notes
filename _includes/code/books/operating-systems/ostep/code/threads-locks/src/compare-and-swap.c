#include <stdio.h>
#include <stdatomic.h>

int global = 0;

char compare_and_swap(int *ptr, int old, int new) {
    unsigned char ret;
    // Note that sete sets a ’byte’ not the word
    __asm__ __volatile__ (
	" lock\n"
	" cmpxchgl %2,%1\n"
	" sete %0\n"
	: "=q" (ret), "=m" (*ptr)
	: "r" (new), "m" (*ptr), "a" (old)
	: "memory");
    return ret;
}

int cas(int* reg, int old, int new) {
  return __sync_val_compare_and_swap(reg, old, new);
}

int main(int argc, char *argv[]) {
    printf("before successful cas: %d\n", global);
    // int success = compare_and_swap(&global, 0, 100);
    int success = cas(&global, 0, 100);
    printf("after successful cas: %d (success: %d)\n", global, success);

    printf("before failing cas: %d\n", global);
    // success = compare_and_swap(&global, 0, 200);
    success = cas(&global, 0, 200);
    printf("after failing cas: %d (old: %d)\n", global, success);

    return 0;
}

