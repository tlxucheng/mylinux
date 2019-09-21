#include <stdio.h>
#include <stdlib.h>

typedef enum{false = 0, true} bool;

bool is_power_of_2(unsigned long n)
{
    return (n !=0 && ((n & (n - 1) == 0));
}

struct kfifo
{
    unsigned char *buffer;
    unsigned int size;
    unsigned int in;
    unsigned int out;
};

void kfifo_init(struct kfifo *fifo, void *buffer, unsigned int size)
{

    return;
}
