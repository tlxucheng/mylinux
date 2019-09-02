#include <stdio.h>
#include <string.h>

struct rb_node {
    unsigned long  __rb_parent_color;
    struct rb_node *rb_right;
    struct rb_node *rb_left;
} __attribute__((aligned(sizeof(long))));

struct rb_root {
    struct rb_node *rb_node;
};

struct mytype {
    struct rb_node node;
    int num;;
};

#define RB_ROOT	(struct rb_root) { NULL, }

struct rb_root mytree = RB_ROOT;

#define TRUE   1
#define FALSE  0


#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);\
        (type *)( (char *)__mptr - offsetof(type,member) );})

/* rb_tree basic function */
void dummy_rotate(struct rb_node *old, struct rb_node *new)
{
 	return;
}

void rb_link_node(struct rb_node *node, struct rb_node *parent,
				struct rb_node **rb_link)
{
	node->__rb_parent_color = (unsigned long)parent;
	node->rb_left = node->rb_right = NULL;

	*rb_link = node;

	return;
}

void __rb_insert(struct rb_node *node, struct rb_root *root, void (*augment_rotate)(struct rb_node *old, struct rb_node *new))
{
    return;
}

void rb_insert_color(struct rb_node *node, struct rb_root *root)
{	
	__rb_insert(node, root, dummy_rotate);

	return;
}


int my_insert(struct rb_root *root, struct mytype *data)
{
    struct rb_node **new = &(root->rb_node);
    struct rb_node *parent = NULL;
    struct mytype  *this = NULL;
    int            result = 0;

    while(*new)
    {
        this = container_of(*new, struct mytype, node);
		result = data->num - this->num;
    }    

    parent = *new;
    if(result < 0)
    {
		new = &((*new)->rb_left);
    }
    else if(result > 0)
    {
		new = &((*new)->rb_right);
    }
    else
    {
		return FALSE;
    }

    rb_link_node(&data->node, parent, new);
    rb_insert_color(&data->node, root);

    return TRUE;
}

struct mytype *my_search(struct rb_root *root, int num)
{
    struct rb_node *node = root->rb_node;
    struct mytype  *data = NULL;
    int            result = 0;

    while(node)
    {
	data = container_of(node, struct mytype, node);

	result = num - data->num;
	if(result < 0)
        {
	    node = node->rb_left;
	}
	else if(result > 0)
	{
	    node = node->rb_right;
	}
	else
	{
	    return data;
	}
    }

    return NULL;
}

int main()
{
    struct mytype data;

    data.node

    my_insert(struct rb_root *root, struct mytype *data); 

    return 0;
}
