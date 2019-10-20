#include "zmalloc.h"

void *zmalloc(size_t size)
{
    void *ptr = malloc(size+PREFIX_SIZE);
}


