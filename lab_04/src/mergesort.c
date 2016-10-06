#include <stdlib.h>

void copy(char *a, char *b, size_t size){
    size_t i;
    for (i = 0; i < size; i++)
        *a++ = *b++;
}

int mergesort (void *base, size_t num, size_t size, int (*compar)(const void* ,const void*)){
    if (num <= 1)
        return 0;
    void *left = base;
    void *mid = (char*)base + (num / 2) * size;
    void *right = (char*)base + size * num;
    mergesort(left, num / 2, size, compar);
    mergesort(mid, num - num / 2, size, compar);
    void *p1 = left, *p2 = mid;
    void *tmp = malloc(size * num), *nxt = tmp;
    while (p1 != mid || p2 != right){
        if (p2 == right || (p1 != mid && compar(p1, p2) < 0)){
            copy(nxt, p1, size);
            p1 = (char*)p1 + size;
        }
        else{
            copy(nxt, p2, size);
            p2 = (char*)p2 + size;
        }
        nxt = (char*)nxt + size;
    }
    void *p;
    for (nxt = tmp, p = base; nxt != (char*)tmp + num * size;
         nxt =(char*)nxt + size, p = (char*)p + size)
        copy(p, nxt, size);
    free(tmp);
}
