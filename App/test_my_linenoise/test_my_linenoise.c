#include <stdio.h>
#include <string.h>

int main()
{
    char input_buf[1024] = {0};
    
    while(1)
    {
        printf("hello> ");
        fflush(stdout);
        scanf("%s", input_buf);
        printf("echo: '%s'\n", input_buf);
        fflush(stdout);
        memset(input_buf, 0x0, sizeof(input_buf));        
    }

    return 0;
}


