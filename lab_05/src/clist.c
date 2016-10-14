#include "../include/clist.h"

void init_list(struct intrusive_list *l){
    l->head = NULL;
}

void add_node(struct intrusive_list *l, struct intrusive_node *node){
    node->next = l->head;
    if (l->head != NULL)
        l->head->prev = node;

    l->head = node;
}

void remove_node(struct intrusive_list *l, struct intrusive_node *node){
        if (node == l->head){
            l->head = node->next;
        }
        else{
            node->prev->next = node->next;
            if (node->next != NULL)
                node->next->prev = node->prev;
        }
}

void apply(struct intrusive_list *l, void (*op)(void*, void*), void *arg){
    struct intrusive_node *node = l->head;
    while (node){
        op(node, arg);
        node = node->next;
    }
}
