#include <stdio.h>
#include <stdlib.h>

#define kmalloc(x) malloc(x)
#define kfree(x) do { if (x) free(x); } while (0)

#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })
#endif

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

void kfifo_reset(struct kfifo *fifo)
{
    fifo->in = 0;
    fifo->out = 0;

    return;
}

void _kfifo_init(struct kfifo *fifo, void *buffer, unsigned int size)
{ 
    fifo->buffer = buffer;
    fifo->size = size;
  
    return;
}

void kfifo_init(struct kfifo *fifo, void *buffer, unsigned int size)
{
    if(!is_power_of_2(size))
    {
        return;
    }

    _kfifo_init(fifo, buffer, size);

    return;
}

int kfifo_alloc(struct kfifo *fifo, unsigned int size)
{
    unsigned char *buffer;

    if(!is_power_of_2(size))
    {
          return -1;
    }

    buffer = kmalloc(size);
    if(!buffer)
    {
        _kfifo_init(fifo, NULL, 0);
        return -1;
    }

    _kfifo_init(fifo, buffer, size);
 
    return 0;
}

void kfifo_free(struct kfifo *fifo)
{
    kfree(fifo->buffer);
    _kfifo_init(fifo, NULL, 0);

    return;
}

void __kfifo_in_data(struct kfifo *fifo, const void *from, unsigned int len, unsigned int off)
{
    unsigned int left;

    left = min(len, fifo->size);
    memcpy(fifo->buffer, from, left);
    memcpy(fifo->buffer, from+left, len - left);

    return;
}

unsigned int kfifo_in(struct kfifo *fifo, const void *from, unsigned int len)
{
    

    return;
}

