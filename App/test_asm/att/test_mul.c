#include<stdio.h>

int main()
{
    int a = 10;
    int b = 0;
    int c = 2;

    __asm__("imull %1, %2\n\t"
        "movl %2, %0"
	:"=r"(b)
	:"r"(a), "r"(c) 
    );

    printf("result: %d\n", b);

    return 0;
}
