#include <stdio.h>

struct rb_node {
    unsigned long  __rb_parent_color;
    struct rb_node *rb_right;
    struct rb_node *rb_left;
} __attribute__((aligned(sizeof(long))));

struct rb_root {
    struct rb_node *rb_node;
};

struct rb_node *rb_red_parent(struct rb_node *red)
{
    return (struct rb_node *)red->__rb_parent_color;
}

struct mytype {
    struct rb_node node;
    char *keystring;
};

#define RB_ROOT	(struct rb_root) { NULL, }

struct rb_root mytree = RB_ROOT;

int main()
{
    return 0;
}
