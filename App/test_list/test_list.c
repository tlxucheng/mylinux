#include <stdio.h>
#include <stdlib.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);\
        (type *)( (char *)__mptr - offsetof(type,member) );})

struct list_head {
	struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
         struct list_head name = LIST_HEAD_INIT(name)

static inline void __list_add(struct list_head *new,
                              struct list_head *prev,
                              struct list_head *next)
{ 
         next->prev = new;
         new->next = next;
         new->prev = prev;
         prev->next = new;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
         __list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
         __list_add(new, head->prev, head);
}

#define list_entry(ptr, type, member) \
        container_of(ptr, type, member)

#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

#define list_last_entry(ptr, type, member) \
	list_entry((ptr)->prev, type, member)

#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)

#define list_prev_entry(pos, member) \
	    list_entry((pos)->member.prev, typeof(*(pos)), member)

#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev; pos != (head); pos = pos->prev

#define list_for_each_safe(pos, n, head) \
        for (pos = (head)->next, n = pos->next; pos != (head); \
                 pos = n, n = pos->next)


#define list_for_each_prev_safe(pos, n, head) \
        for (pos = (head)->prev, n = pos->prev; \
                 pos != (head); \
                 pos = n, n = pos->prev)

#define list_for_each_entry(pos, head, member)                          \
for (pos = list_first_entry(head, typeof(*pos), member);        \
                 &pos->member != (head);                                    \
                 pos = list_next_entry(pos, member))


struct my_test_data
{
   int data;
   struct list_head lru;
};

int main()
{
    //my_test_data        *head_node = (my_test_data *)malloc(sizeof(my_test_data));
    int                        i          = 0;
    struct my_test_data        *node      = NULL;
    struct list_head           *temp      = NULL;           
    struct my_test_data        *temp_data = NULL;

    //LIST_HEAD(head_node->lru);
    LIST_HEAD(g_head_node);

    for(i = 0; i < 10; i++)
    {
    	node = (struct my_test_data *)malloc(sizeof(struct my_test_data));
    	node->data = i+1;
	//list_add(&node->lru, &g_head_node);
	list_add_tail(&node->lru, &g_head_node);
    }

    list_for_each(temp, &g_head_node) 
    {
        temp_data = list_entry(temp, struct my_test_data, lru);	
	printf("data: %d\n", temp_data->data);
    }

    return 0;
}

