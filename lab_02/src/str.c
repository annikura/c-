#include <stdlib.h>

size_t strlen(const char * str){
    size_t size = 0;
    while (*(str + size)) size++;
    return size;
}

char * strcpy(char * destination, const char * source){
    size_t pointer = 0;
    while (*(source + pointer))
        *(destination + pointer) = *(source + pointer), pointer++;
    *(destination + pointer) = '\0';
    return destination;
}


char * strcat(char * destination, const char * source){
    strcpy(destination + strlen(destination), source);
    return destination;
}

int strcmp(const char * str1, const char * str2){
    while (*str1 || *str2){
        if (*str1 != *str2)
            return *str1 - *str2;
        str1++, str2++;
    }
    return 0;
}
