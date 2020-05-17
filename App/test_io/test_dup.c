#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void write_file_use_dup_func()
{
   int oldfd = open("mytest1",O_RDWR | O_CREAT,0644);
    
   close(STDOUT_FILENO);
   dup(oldfd);
   close(oldfd); 
  
   printf("hello world mytest1\n");
   fflush(stdout);
  
   return;
}

void write_file_use_dup2_func()
{
   int oldfd = open("mytest2",O_RDWR | O_CREAT,0644);
    
   dup2(oldfd, STDOUT_FILENO);
   close(oldfd); 
  
   printf("hello world mytest2\n");
   fflush(stdout);

   return;
}

int ioStdSet(int src_fd, int dest_fd, int *save_fd) 
{
    *save_fd = dup(dest_fd);
    dup2(src_fd, dest_fd);
    //close(src_fd);
    return *save_fd;
}

void recoverIoStdSet(int src_fd, int dest_fd) 
{
    dup2(src_fd, dest_fd);
    close(src_fd);
}

void set_and_recover()
{
    int save_fd = 0;

    int oldfd = open("mytest3",O_RDWR | O_CREAT,0644);

    ioStdSet(oldfd, STDOUT_FILENO, &save_fd);     
    printf("hello world mytest3\n");
    fflush(stdout);
    recoverIoStdSet(save_fd, STDOUT_FILENO); 
    printf("hello world mytest3\n");
}

int main(int argc, char* argv[])
{
    set_and_recover();

    return 0;
}

