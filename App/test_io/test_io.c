#include <stdio.h>
#include <unistd.h>

int main()	 
{
    char buf[1024] = {"Hello World!\n"};

    fprintf(stderr,"stderr!\n");
    fprintf(stdout,"stdout!\n");
    printf("printf!\n");
    perror("test perror func\n");

    write(STDOUT_FILENO, buf, sizeof(buf));
    write(STDERR_FILENO, buf, sizeof(buf));

    return 0;    
}
