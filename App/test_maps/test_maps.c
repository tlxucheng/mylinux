#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char cmd_str[1024] = {0};
    pid_t pid;

    pid = getpid();
    printf("test_maps pid: %d\n", pid);
    snprintf(cmd_str, sizeof(cmd_str), "cat /proc/%d/maps", pid);
    system(cmd_str);

    return 0;
}
