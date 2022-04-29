#include <stdio.h>

void func() {
  int x = 3000;
  x += 3;
}

/*
Interposition moves 3000 to the register rbp -4, then moves
rbp to eax
then it
Ltmp0:
	.loc	1 4 7 prologue_end      ## src/interposition.c:4:7
	movl	$3000, -4(%rbp)         ## imm = 0xBB8
	.loc	1 5 5                   ## src/interposition.c:5:5
	movl	-4(%rbp), %eax
	addl	$3, %eax
	movl	%eax, -4(%rbp)
	.loc	1 6 1                   ## src/interposition.c:6:1
	popq	%rbp
	retq
*/

int main() {
  func();
}
