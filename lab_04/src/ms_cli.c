#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/mergesort.h"

int intcmp(const void *a, const void *b){
    return atoi(*(char**)a) - atoi(*(char**)b);
}

int my_strcmp(const void *a, const void *b){
    char *x = *(char**)a;
    char *y = *(char**)b;
    return strcmp(x, y);
}

int main(int argc, char* argv[])
{
    int i;
    if (strcmp(argv[1], "int") == 0){
         mergesort((void*)(argv + 2), argc - 2, sizeof(char**), intcmp);
    }
    if (strcmp(argv[1], "char") == 0 || strcmp(argv[1], "str") == 0){
        mergesort((void*)(argv + 2), argc - 2, sizeof(char**), my_strcmp);
    }
    for (i = 2; i < argc; i++)
        printf("%s ", argv[i]);
    return 0;
}
