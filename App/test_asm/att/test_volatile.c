#include <stdio.h>

int main()
{
    char input[30]  = {"Hello inline assembly.\n"};
    char output[30] = {0};
    int  len        = 24;

    __asm__ __volatile__ (
		    "cld\n\t"
		    "rep movsb\n\t"
		    :
		    : "S"(input),"D"(output),"c"(len)
		    );

    printf("%s\n", output);

    return 0;
}
