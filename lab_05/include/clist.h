#ifndef __CLIST

#define __CLIST
#include <stdlib.h>
#include <stddef.h>

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct intrusive_node {
    struct intrusive_node* next;
    struct intrusive_node* prev;
};

struct intrusive_list {
    struct intrusive_node* head;
    size_t sz;
};

void init_list(struct intrusive_list* l);
void add_node(struct intrusive_list* l, struct intrusive_node* node);
void remove_node(struct intrusive_list* l, struct intrusive_node* node);
void apply(struct intrusive_list *l, void (*op)(void*, void*), void *arg);


#endif // __CLIST

