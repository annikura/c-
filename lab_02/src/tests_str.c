#include <stdio.h>
#include "../include/str.h"

const size_t SIZE = 100;

int sign(int x){
    if (x < 0)
        return -1;
    if (x > 0)
        return 1;
    return 0;
}

void cut_tails(char *s){
    int x = strlen(s);
    while (s[0] && s[x - 1] == '\n')
        s[--x] = '\0';
}

void test_strlen(int n){
    char s[SIZE];
    int length, i;
    freopen("../tests/test_strlen.in", "r", stdin);
    if (strlen("") != 0)
        printf("0 is wrong on strlen\n");
    for (i = 0; i < n; i++){
        fgets(s, SIZE, stdin);
        cut_tails(s);
        scanf(" %d ", &length);
        if (length != strlen(s))
            fprintf(stderr, "oh no! something's wrong with the strlen on test %d\n", i);
    }

    fclose(stdin);
}

void test_strcat(int n){
    char s1[SIZE], s2[SIZE], ans[SIZE];
    int i;

    freopen("../tests/test_strcat.in", "r", stdin);

    for (i = 0; i < n; i++){
        fgets(s1, SIZE, stdin);
        fgets(s2, SIZE, stdin);
        fgets(ans, SIZE, stdin);
        cut_tails(s1), cut_tails(s2), cut_tails(ans);
        if (strcmp(strcat(s1, s2), ans) != 0)
            fprintf(stderr, "oh no! something's wrong with the strcat on test %d\n", i);
    }

    fclose(stdin);
}

void test_strcpy(int n){
    char s1[SIZE], s2[SIZE], ans[SIZE];
    int i;

    freopen("../tests/test_strcpy.in", "r", stdin);

    for (i = 0; i < n; i++){
        fgets(s1, SIZE, stdin);
        fgets(s2, SIZE, stdin);
        fgets(ans, SIZE, stdin);
        cut_tails(s1), cut_tails(s2), cut_tails(ans);
        if (strcmp(strcpy(s1, s2), ans) != 0)
            fprintf(stderr, "oh no! something's wrong with the strcpy on test %d\n", i);
    }

    fclose(stdin);
}

void test_strcmp(int n){
    char s1[SIZE], s2[SIZE];
    int ans, i;
    freopen("../tests/test_strcmp.in", "r", stdin);

    for (i = 0; i < n; i++){
        fgets(s1, SIZE, stdin);
        fgets(s2, SIZE, stdin);
        scanf(" %d ", &ans);
        cut_tails(s1), cut_tails(s2);
        if (sign(ans) != sign(strcmp(s1, s2))){
            fprintf(stderr, "oh no! something's wrong with the strcmp on test %d\n", i);
        }
    }

    fclose(stdin);
}
