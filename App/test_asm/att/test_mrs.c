#include <stdio.h>

int main()
{
    int a = 1;
    int b = 2;
    unsigned int eax;

    printf("test mrs\n");

    /*
    asm("mov %0, sp"
	:"=r"(sp)
	:
	: "cc"
       );
    */

    asm("movl %0, %%eax" : "=r" (eax) : : "cc");
    printf("eax: 0x%x", eax);

    return 0;
}
