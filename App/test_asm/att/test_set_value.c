#include <stdio.h>

int main()
{
    int dest;
    int value = 1;

    asm(
    "movl %1, %0"
    : "=a"(dest)
    : "c"(value)
    : "%ebx");

    printf("%d\n", dest);

    return 0;
}
