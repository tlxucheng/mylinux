#include <stdio.h>

int main()
{
#ifdef FUN1
    printf("fun1 print.\n");
#else
    printf("fun2 print.\n");
#endif

    return 0;
}
