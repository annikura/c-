#include "../include/clist.h"

void init_list(struct intrusive_list * l){
    l->head = NULL;
    l->sz = 0;
}

void add_node(struct intrusive_list* l, struct intrusive_node* node){
    node->next = l->head;
    if (l->head != NULL)
        l->head->prev = node;

    l->sz++;
    l->head = node;
}

void remove_node(struct intrusive_list* l, struct intrusive_node* node){
        if (node == l->head){
            l->head = node->next;
        }
        else{
            node->prev->next = node->next;
            if (node->next != NULL)
                node->next->prev = node->prev;
        }

        l->sz--;
}

size_t get_length(struct intrusive_list* l){
    return l->sz;
}
