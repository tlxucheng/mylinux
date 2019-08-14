#include <stdio.h>

int main()
{
    unsigned int val1 = 1;
    unsigned int val2 = 2;
    unsigned int val3 = 0;

    printf("val1:%d, val2:%d, val3: %d\n", val1, val2, val3);
    asm volatile(
        "mov $0, %%eax\n\t"
        "addl %0, %%eax\n\t"
        "addl %1, %%eax\n\t"
	"movl %%eax, %2\n\t"
	: "=m" (val3)
	: "c" (val1), "d" (val2)
    );

    printf("val1:%d, val2:%d, val3: %d\n", val1, val2, val3);

    return 0;
}
