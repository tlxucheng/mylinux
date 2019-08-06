#include <stdio.h>

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

struct list_head {
    struct list_head *next；
    struct list_head  *prev;
};

struct ipstore{
    unsigned long time;
    __u32 addr[4];
    struct list_head list;
};

int main()
{
    struct ipstore ip1;
    struct ipstore *p1;

    p1 = container_of(&ip1.list, struct ipstore, list);

    printf("ip1's addr:%p\n", &ip1);
    printf("p1's  addr:%p\n", p1);
    return 0;
}
