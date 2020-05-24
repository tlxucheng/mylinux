#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void sig_usr(int signo)
{
    if(SIGUSR1 == signo)
    {
        printf("received SIGUSR1\n");
    }
    else if(SIGUSR2 == signo)
    {    
        printf("received SIGUSR2\n");
    }
    else if(SIGINT == signo)
    {
        printf("received ctrl+c\n");
        exit(0);
    }
    else 
    {
        printf("received signal %d\n", signo);
    } 

    return;
}

int main()
{
    if(signal(SIGUSR1, sig_usr) == SIG_ERR)
    {
        printf("can,t catch SIGUSR1");
    }

    if(signal(SIGUSR2, sig_usr) == SIG_ERR)
    {
        printf("can,t catch SIGUSR2");
    }    

    if(signal(SIGINT, sig_usr) == SIG_ERR)
    {
        printf("can,t catch SIGINT");
    }    

    for(;;)
    {
        pause();
    }

    return 0;
}


