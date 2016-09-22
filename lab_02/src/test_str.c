#include <stdio.h>
#include "../include/str.h"

const size_t SIZE = 100;

//as far as i can either use my functions or write them one more time
//but in that file, the testing code is so disgusting. Very pity.
//So yep, each test is in its own function. If they were not so,
//i'd had to use my functions to copy or whatever else them.

int sign(int x){
    if (x < 0)
        return -1;
    if (x > 0)
        return 1;
    return 0;
}

//strlen block

void check_len1(){
    char in[] = "";
    int ret = 0;
    if (strlen(in) != ret)
        fprintf(stderr, "len1 not ok");
}

void check_len2(){
    char in[] = "aaa";
    int ret = 3;
    if (strlen(in) != ret)
        fprintf(stderr, "len2 not ok");
}

void check_len3(){
    char in[] = "i will do it! sooner or later...";
    int ret = 32;
    if (strlen(in) != ret)
        fprintf(stderr, "len3 not ok");
}

void check_len4(){
    char in[] = "abacaba";
    int ret = 7;
    if (strlen(in) != ret)
        fprintf(stderr, "len4 not ok");
}

void test_strlen(){
    check_len1();
    check_len2();
    check_len3();
    check_len4();
}

//strcat block

//assuming that my strcmp works according to the tests below

void check_cat1(){
    char in[] = "";
    char out[] = "";
    char res[] = "";
    if (strcmp(strcat(in, out), res) != 0)
        fprintf(stderr, "cat1 not ok\n");
}

void check_cat2(){
    char in[] = "";
    char out[] = "red";
    char res[] = "red";
    if (strcmp(strcat(in, out), res) != 0)
        fprintf(stderr, "cat2 not ok\n");
}

void check_cat3(){
    char in[] = "blue";
    char out[] = "";
    char res[] = "blue";
    if (strcmp(strcat(in, out), res) != 0)
        fprintf(stderr, "cat3 not ok\n");
}


void check_cat4(){
    char in[] = "once in a";
    char out[] = " blue moon i will be able to write it";
    char res[] = "once in a blue moon i will be able to write it";
    if (strcmp(strcat(in, out), res) != 0)
        fprintf(stderr, "cat4 not ok\n");
}

void check_cat5(){
    char in[] = "hurry up!";
    char out[] = "The deadline is coming!";
    char res[] = "hurry up!The deadline is coming!";
    if (strcmp(strcat(in, out), res) != 0)
        fprintf(stderr, "cat5 not ok\n");
}

void test_strcat(){
    check_cat1();
    check_cat2();
    check_cat3();
    check_cat4();
    check_cat5();
}

// strcpy block

void check_cpy1(){
    char in[] = "hurry up!";
    char out[] = "The deadline is coming!";
    char res[] = "The deadline is coming!";
    if (strcmp(strcpy(in, out), res) != 0)
        fprintf(stderr, "cpy1 not ok\n");
}

void check_cpy2(){
    char in[] = "";
    char out[] = "";
    char res[] = "";
    if (strcmp(strcpy(in, out), res) != 0)
        fprintf(stderr, "cpy2 not ok\n");
}

void check_cpy3(){
    char in[] = "shorter";
    char out[] = "looonger";
    char res[] = "looonger";
    if (strcmp(strcpy(in, out), res) != 0)
        fprintf(stderr, "cpy3 not ok\n");
}

void check_cpy4(){
    char in[] = "but now its longer";
    char out[] = "and shorter";
    char res[] = "and shorter";
    if (strcmp(strcpy(in, out), res) != 0)
        fprintf(stderr, "cpy4 not ok\n");
}

void check_cpy5(){
    char in[] = "";
    char out[] = "and shor";
    char res[] = "and shor";
    if (strcmp(strcpy(in, out), res) != 0)
        fprintf(stderr, "cpy5 not ok\n");
}

void check_cpy6(){
    char in[] = "wooop";
    char out[] = "";
    char res[] = "";
    if (strcmp(strcpy(in, out), res) != 0)
        fprintf(stderr, "cpy6 not ok\n");
}

void test_strcpy(){
    check_cpy1();
    check_cpy2();
    check_cpy3();
    check_cpy4();
    check_cpy5();
    check_cpy6();
}

//strcmp block

void check_cmp1(){
    char in[] = "";
    char out[] = "";
    int res = 0;
    if (sign(strcmp(in, out)) != sign(res))
        fprintf(stderr, "cmp1 not ok\n");
}


void check_cmp2(){
    char in[] = "";
    char out[] = "aaa";
    int res = -1;
    if (sign(strcmp(in, out)) != sign(res))
        fprintf(stderr, "cmp2 not ok\n");
}


void check_cmp3(){
    char in[] = "erer";
    char out[] = "";
    int res = 1;
    if (sign(strcmp(in, out)) != sign(res))
        fprintf(stderr, "cmp3 not ok\n");
}


void check_cmp4(){
    char in[] = "aa";
    char out[] = "aaaaa";
    int res = -1;
    if (sign(strcmp(in, out)) != sign(res))
        fprintf(stderr, "cmp4 not ok\n");
}

void check_cmp5(){
    char in[] = "safl";
    char out[] = "safew";
    int res = 1;
    if (sign(strcmp(in, out)) != sign(res))
        fprintf(stderr, "cmp5 not ok\n");
}

void test_strcmp(){
    check_cmp1();
    check_cmp2();
    check_cmp3();
    check_cmp4();
    check_cmp5();
}

