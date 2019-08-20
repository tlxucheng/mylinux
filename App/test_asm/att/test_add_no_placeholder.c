#include <stdio.h>

int main()
{
    unsigned int val1 = 1;
    unsigned int val2 = 2;
    unsigned int val3 = 0;
    
    __asm__(
    "addl %%ecx, %%edx"
    :"=d" (val3)
    :"c" (val1), "d" (val2)
    );

    printf("val3: %d\n", val3);

    return 0;
}
