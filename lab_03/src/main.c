#include <string.h>
#include <stdio.h>
#include "../include/clist.h"

struct position_node{
    int x, y;
    struct intrusive_node node;
};

void remove_position(struct intrusive_list* l, int x, int y) { // removes all (x, y) pairs
    struct intrusive_node* node = l->head, *nxt;
    while (node != NULL){
        nxt = node->next;
        struct position_node* pos_node = container_of(node, struct position_node, node);
        if (x == pos_node->x && y == pos_node->y){
            remove_node(l, node);

            free(pos_node);

        }
        node = nxt;
    }
}

void add_position(struct intrusive_list* l, int x, int y) {
    struct position_node* node = malloc(sizeof(struct position_node));
    node->x = x, node->y = y;
    add_node(l, &(node->node));
}

void show_all_positions(struct intrusive_list* l) {
    struct intrusive_node* node = l->head, *nxt;
    while (node != NULL){
        nxt = node->next;
        struct position_node* pos_node = container_of(node, struct position_node, node);
        if (l->head != node)
            printf(" ");
        printf("(%d %d)", pos_node->x, pos_node->y);
        node = nxt;
    }
    printf("\n");
}

void remove_all_positions(struct intrusive_list* l) {
    while (l->head != NULL){
        struct position_node* pos_node = container_of(l->head, struct position_node, node);
        remove_node(l, l->head);

        free(pos_node);

    }
}

int main() {
    struct intrusive_list l;
    init_list(&l);
    char command[10];
    while (1){
        scanf("%s", command);
        if (strcmp(command, "add") == 0){
            int x, y;
            scanf("%d%d", &x, &y);
            add_position(&l, x, y);
            continue;
        }
        if (strcmp(command, "rm") == 0){
            int x, y;
            scanf("%d%d", &x, &y);
            remove_position(&l, x, y);
            continue;
        }
        if (strcmp(command, "print") == 0){
            show_all_positions(&l);
            continue;
        }
        if (strcmp(command, "rma") == 0){
            remove_all_positions(&l);
            continue;
        }
        if (strcmp(command, "len") == 0){
            printf("%zu\n", get_length(&l));
            continue;
        }
        if (strcmp(command, "exit") == 0){
            return 0;
        }
        printf("Unknown command\n");
    }
    return 0;
}
