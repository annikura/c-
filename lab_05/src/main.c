#include <string.h>
#include <stdio.h>
#include "../include/clist.h"

struct position_node{
    int x, y;
    struct intrusive_node node;
};

void remove_position(struct intrusive_list *l, int x, int y) { // removes all (x, y) pairs
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

void add_position(struct intrusive_list* l, int x, int y){
    struct position_node* node = malloc(sizeof(struct position_node));
    node->x = x, node->y = y;
    add_node(l, &(node->node));
}

void show_all_positions(struct intrusive_list* l){
    struct intrusive_node* node = l->head, *nxt;
    while (node != NULL){
        nxt = node->next;
        struct position_node* pos_node = container_of(node, struct position_node, node);
        printf("(%d %d)\n", pos_node->x, pos_node->y);
        node = nxt;
    }
    printf("\n");
}

void print_node(void *node_void, void *fmt_void){
    char *fmt = (char *)fmt_void;
    struct intrusive_node *node = (struct intrusive_node *) node_void;
    struct position_node* pos_node = container_of(node, struct position_node, node);
    printf(fmt, pos_node->x, pos_node->y);
}

void count(void * node, void *cnt){
    if ((struct intrusive_node*)node)
        (*(int *)cnt)++;
}

void remove_all_positions(struct intrusive_list* l){
    while (l->head != NULL){
        struct position_node* pos_node = container_of(l->head, struct position_node, node);
        remove_node(l, l->head);
        free(pos_node);

    }
}

void reverse(struct intrusive_list *l){
    struct intrusive_list tmp;
    init_list(&tmp);
    struct intrusive_node *node = l->head;
    while (node){
        struct position_node* pos_node = container_of(node, struct position_node, node);
        add_position(&tmp, pos_node->x, pos_node->y);
        node = node->next;
    }
    remove_all_positions(l);
    l->head = tmp.head;
}

void loadbin(struct intrusive_list *l, char *filename){
    FILE *f = fopen(filename, "rb");
    while (!feof(f)){
        int num_x = 0, num_y = 0, succ = 0;
        succ = fread((void *)&num_x, sizeof(char), 3, f);
        succ = fread((void *)&num_y, sizeof(char), 3, f);
        if (succ)
            add_position(l, num_x, num_y);
    }
    reverse(l);
    fclose(f);
}

void loadtext(struct intrusive_list *l, char *filename){
    FILE *f = fopen(filename, "rt");
    while (!feof(f)){
        int num_x = 0, num_y = 0, succ = 0;
        succ = fscanf(f, "%d%d", &num_x, &num_y);
        if (succ != -1)
            add_position(l, num_x, num_y);
    }
    reverse(l);
    fclose(f);
}

void savebin(struct intrusive_list *l, char *filename){
    FILE *f = fopen(filename, "wb");
    struct intrusive_node *node = l->head;
    while (node){
        struct position_node* pos_node = container_of(node, struct position_node, node);
        fwrite((void *)&pos_node->x, sizeof(char), 3, f);
        fwrite((void *)&pos_node->y, sizeof(char), 3, f);
        node = node->next;
    }
    fclose(f);
}


void savetext(struct intrusive_list *l, char *filename){
    FILE *f = fopen(filename, "wt");
    struct intrusive_node *node = l->head;
    while (node){
        struct position_node* pos_node = container_of(node, struct position_node, node);
        fprintf(f, "%d %d\n", pos_node->x, pos_node->y);
        node = node->next;
    }
    fclose(f);
}

int main(int argc, char *argv[]){
    struct intrusive_list l;
    init_list(&l);
    if (strcmp(argv[1], "loadbin") == 0)
        loadbin(&l, argv[2]);
    else if (strcmp(argv[1], "loadtext") == 0)
        loadtext(&l, argv[2]);
    else{
        printf("Unknown command %s\n", argv[1]);
        exit(0);
    }
    if (strcmp(argv[3], "print") == 0){
        apply(&l, print_node, (void *)argv[4]);
        printf("\n");
    }
    else if (strcmp(argv[3], "count") == 0){
        int len = 0;
        apply(&l, count, (void *)&len);
        printf("%d\n", len);
    }
    else if (strcmp(argv[3], "savetext") == 0){
        savetext(&l, argv[4]);
    }
    else if (strcmp(argv[3], "savebin") == 0){
        savebin(&l, argv[4]);
    }
    else{
        printf("Unknown command %s\n", argv[3]);
    }
    remove_all_positions(&l);
    return 0;
}
