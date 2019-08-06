#include <unistd.h>  
#include <signal.h>  
#include <stdlib.h>  
#include <string.h>  
#include <fcntl.h>  
#include <sys/stat.h>  
#include <time.h>  
#include <stdio.h>  
      
#define true  1
#define false 0

static int flag = true;  

void create_daemon()  
{  
    pid_t 	pid;  
    int 	i   = 0;  

    pid = fork();
    if(pid == -1)  
    {  
        printf("fork error\n");  
        exit(1);  
    }  
    else if(pid)  
    {  
        exit(0);  
    }  
  
    if(-1 == setsid())  
    {  
        printf("setsid error\n");  
        exit(1);  
    }  
  
    pid = fork();  
    if(pid == -1)  
    {  
        printf("fork error\n");  
        exit(1);  
    }  
    else if(pid)  
    {  
        exit(0);  
    }  
  
    chdir("/");  
    
    for(i = 0; i < 3; ++i)  
    {  
        close(i);  
    } 

    umask(0);  
   
    return;  
}  

void handler(int sig)
{
    printf("I got a signal %d\nI'm quitting.\n", sig);
    flag = false;
}

void sig_process()
{
    struct sigaction act;
    
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if(sigaction(SIGQUIT, &act, NULL))
    {
        printf("sigaction error.\n");
        exit(0);
    }

    return;
}

void write_time()
{
    int    fd;
    char   buf[2048] = {0};

    fd = fopen("/var/log/kern.log", "r");
    if(fd == -1)
    {
    	printf("open error\n");
    }
  
    while(fgets(buf, sizeof(buf), fd)) 
    {
    	printf("%s\n", buf);
    }

    fclose(fd);
    sleep(5);

    return;
}

int main()  
{  
    time_t t;  
    int fd;  
        
    create_daemon();  
      
    sig_process();  
      
    while(flag)  
    {
        write_time();
    }  
 
    return 0;  
 }  
    
