#include <stdio.h>
#include <stdarg.h>

int my_sum(int num, ... )
{
	int sum = 0;
    va_list valist;
	int i = 0;

	va_start(valist, num);
    for(i = 0; i < num; i++)
    {
	    sum += va_arg(valist, int);
	}
	va_end(valist);

    return sum;
}

int main()
{
    int sum = 0;

    sum = my_sum(3, 1, 3, 5);
	printf("sum: %d\n", sum);

    return 0;
}
