#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int main()
{
    pid_t   pid;
    int     inc = 3;
    int     prio;

    pid = fork();
    if(0 == pid) 
    {
    	prio = getpriority(PRIO_PROCESS, getpid());
    	printf("the child's process %d priority is: %d\n", getpid(), prio);

    	nice(inc);
    	prio = getpriority(PRIO_PROCESS, getpid());
   	printf("after nice(%d), the child's process %d priority is:%d\n", inc, getpid(), prio);
    }
    else if(pid < 0) 
    {
        exit(0);
    }

    while(1)
    {
        sleep(10);
    }

    return 0;
}
