#include <stdio.h>

int main()
{
    int num = 0x1234;

    if(0x34 == *(char *)&num)
    {
        printf("Little-Endian\n");
    }
    else 
    {
        printf("Big-Endian\n");
    }

    return 0;
}



