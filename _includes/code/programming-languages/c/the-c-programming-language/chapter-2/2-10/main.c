#include <stdio.h>

char lower(char c) { return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c; }

int main() { printf("%c\n", lower('D')); }
