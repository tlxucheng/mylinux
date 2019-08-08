#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();
    if(0 == pid)
    {
	printf("I am the child process, my process is %d\n", getpid());
    }
    else if(pid > 0)
    {
	printf("I am the parent process, my process is %d\n", getpid());
    }
    else
    {
	printf("fork error!\n");
    }

    return 0;
}
