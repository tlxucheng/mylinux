#include <stdio.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);\
	(type *)( (char *)__mptr - offsetof(type,member) );})

struct test
{
    char a;
    int  b;
    char c;
};

struct test2
{
    char a;
    char b;
    int  c;
};

int main()
{
    struct test temp;

    printf("sizeof(test): %ld\n", sizeof(struct test));
    printf("sizeof(test2): %ld\n", sizeof(struct test2));
    printf("&temp: %p\n", &temp);
    printf("&temp.c: %p\n", &temp.c);
    printf(":container_of_c: %p\n", container_of(&temp.c, struct test, c));
    //printf("((struct *test)0)->c: %d\n", &(((struct test*)0)->c));
    printf("&((struct test *)0)->c: %d\n",((int)&((struct test *)0)->c));

    return 0;
}
