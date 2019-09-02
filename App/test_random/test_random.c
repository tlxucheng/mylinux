#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i   = 0;
    int num = 0;

    for(i = 0; i < 10000; i++)
    {
        num = rand()%10000 + 1;
	printf("%d\n", num);
    }

    return 0;
}
