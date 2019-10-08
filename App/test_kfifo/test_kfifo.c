#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kmalloc(x) malloc(x)
#define kfree(x) do { if (x) free(x); } while (0)

#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })

typedef enum{false = 0, true} bool;

bool is_power_of_2(unsigned long n)
{
    return (n !=0 && ((n & (n - 1)) == 0));
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

    kfifo_reset(fifo);

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

unsigned int __kfifo_off(struct kfifo *fifo, unsigned int off)
{
	return off & (fifo->size - 1);
}

void __kfifo_in_data(struct kfifo *fifo, const void *from, unsigned int len, unsigned int off)
{
    unsigned int left;
 
    off = __kfifo_off(fifo, fifo->in + off);

    left = min(len, fifo->size - off);
    memcpy(fifo->buffer + off, from, left);
    memcpy(fifo->buffer, from+left, len - left);

    return;
}

void __kfifo_add_in(struct kfifo *fifo, unsigned int off)
{
    fifo->in += off;

    return;
}

unsigned int kfifo_in(struct kfifo *fifo, const void *from, unsigned int len)
{
    __kfifo_in_data(fifo, from, len, 0);
	__kfifo_add_in(fifo, len);

    return len;
}

void __kfifo_out_data(struct kfifo *fifo, void *to, unsigned int len, unsigned int off)
{
	unsigned int l;

    off = __kfifo_off(fifo, fifo->out + off);
	l = min(len, fifo->size - off);
	memcpy(to, fifo->buffer + off, l);
	memcpy(to + l, fifo->buffer, len - l);

    return;
}

void __kfifo_add_out(struct kfifo *fifo, unsigned int off)
{
	fifo->out += off;

    return;
}

unsigned int kfifo_out(struct kfifo *fifo, void *to, unsigned int len)
{
	__kfifo_out_data(fifo, to, len, 0);
	__kfifo_add_out(fifo, len);

    return len;
}

int main()
{
    struct kfifo test_fifo;
    int          num        = 16;
    int          i          = 0;
    int          out_num    = 0;

    if (kfifo_alloc(&test_fifo, num * sizeof(unsigned int)))
    {
        return -1;
    }

    for(i = 0; i < num; i++)
    {
        kfifo_in(&test_fifo, (unsigned int *)&i, sizeof(unsigned int));
    }

    kfifo_in(&test_fifo, (unsigned int *)&i, sizeof(unsigned int));

    for(i = 0;i < num; i++)
    {
        kfifo_out(&test_fifo, (unsigned int *)&out_num, sizeof(unsigned int));
        printf("out_num: %d\n", out_num);
    }
    
    kfifo_free(&test_fifo);

    return 0;
}

