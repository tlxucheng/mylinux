#include <stdio.h>

int a = 33;
int b = 22;
int result;

int main()
{
asm ("cmp	%1,	%2\n\t"
	 "jge	greater\n\t"
	 "movl	%1,	%0\n\t"
	 "jmp	end\n"
	 "greater:\n\t"
	 "movl	%2,	%0\n"
	 "end:"
	 : "=r"(result)
	 : "r"(a), "r"(b) );

    printf("result: %d\n", result);

    return 0;
}
