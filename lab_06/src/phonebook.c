#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <expat.h>

#include "../include/phonebook.h"
#include "../include/names.h"

phonebook_t *glob_book;
bool interrupt = true;

int cmp(const void *a, const void *b){
    return strcmp(((human_t *)a)->family_name, ((human_t *)b)->family_name);
}

void add_human(phonebook_t *book, human_t human){
    if (book->capacity == book->size){
        if (book->capacity == 0)
            book->capacity = 1;
        book->capacity *= 2;
        book->humans = (human_t*)realloc(book->humans, sizeof(human_t) * book->capacity);
    }
    book->humans[book->size++] = human;
}

void start_element(void *data, const char *element, const char **attribute){
    interrupt = true;
    if (strcmp(element, "human") == 0){
        human_t human;
        human.phone_cnt = 0;

        char *tmp = (char *)malloc(strlen(attribute[1]));
        strcpy(tmp, attribute[1]);

        char *token = strtok(tmp, " ");
        strcpy(human.name, token);
        token = strtok(NULL, " ");
        strcpy(human.middle_name, token);
        token = strtok(NULL, " ");
        strcpy(human.family_name, token);

        add_human(glob_book, human);

        free(tmp);
        return;
    }
    if (strcmp(element, "phonebook") == 0){
        return;
    }
    if (strcmp(element, "phone") == 0){
        return;
    }
    printf("Unknown field %s\n", element);
    return;
}

void end_element(void *data, const char *element){
    interrupt = true;
    if (strcmp(element, "human") == 0){
        return;
    }
    if (strcmp(element, "phone") == 0){
        return;
    }
    if (strcmp(element, "phonebook") == 0){
        return;
    }
    printf("Unknown ending %s\n", element);
}

bool is_none(const char *str, int length){
    int i;
    for (i = 0; i < length; i++)
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            return false;
    return true;
}

void handle_data(void *data, const char *content, int length){
    if (is_none(content, length)){
        interrupt = true;
        return;
    }

    char *tmp = (char *)malloc(length * sizeof(char));
    strncpy(tmp, content, length);
    tmp[length] = '\0';
    if (interrupt){
        human_t *human = &(glob_book->humans[glob_book->size - 1]);
        strcpy(human->phones[human->phone_cnt], tmp);
        human->phone_cnt++;
    }
    else{
        human_t *human = &(glob_book->humans[glob_book->size - 1]);
        strcat(human->phones[human->phone_cnt - 1], tmp);
    }
    free(tmp);
    interrupt = false;
}

int load_phonebook_xml(const char *filename, phonebook_t *book){
    FILE *fp;
    fp = fopen(filename, "r");

    if (fp == NULL){
        printf("Couldn't open the file %s\n", filename);
        return 1;
    }

    clear_phonebook(book);
    glob_book = book;

    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);

    char *buff = (char *)malloc(BUFF_SIZE * sizeof(char));
    memset(buff, 0, BUFF_SIZE);

    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), BUFF_SIZE, fp);
        done = len < BUFF_SIZE;
        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR){
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
            return 2;
        }
    } while (!done);

    free(buff);
    XML_ParserFree(parser);
    fclose(fp);

    qsort(book->humans, book->size, sizeof(human_t), cmp);

}

int save_phonebook_xml(const char *filename, phonebook_t *book){
    int i, j;
    FILE *fp = fopen(filename, "w");

    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(fp, "<phonebook>\n");
    for (i = 0; i < book->size; i++){
        human_t *pointer = &book->humans[i];
        fprintf(fp, "\t<human name=\"%s %s %s\">\n", pointer->name,
                                                     pointer->middle_name,
                                                     pointer->family_name);
        for (j = 0; j < pointer->phone_cnt; j++)
            fprintf(fp, "\t\t<phone>%s</phone>\n", pointer->phones[j]);
        fprintf(fp, "\t</human>\n");
        pointer++;
    }
    fprintf(fp, "</phonebook>\n\n");
    fclose(fp);
}

void print_phonebook(phonebook_t *book){
    int i, j;

    printf("%zu\n", book->size);

    for (i = 0; i < book->size; i++){
        human_t *pointer = &(book->humans[i]);
        printf("name: %s\n", pointer->name);
        printf("middle name: %s\n", pointer->middle_name);
        printf("family name: %s\n", pointer->family_name);
        for (j = 0; j < pointer->phone_cnt; j++)
            printf("phone: %s\n", pointer->phones[j]);
        printf("\n");
    }
}

human_t get_random_human(){
    int i, j;

    human_t human;
    strcpy(human.name, kNames[rand() % NAMES_CNT]);
    strcpy(human.family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);
    strcpy(human.middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
    human.phone_cnt = rand() % 10;
    for (i = 0; i < human.phone_cnt; i++){
        int len = rand() % 19 + 1;
        for (j = 0; j < len; j++)
            human.phones[i][j] = rand() % 10 + '0';
        human.phones[i][len] = '\0';
    }
    return human;
}

void gen_phonebook(phonebook_t *book, size_t size){
    int i;
    clear_phonebook(book);
    for (i = 0; i < size; i++){
        human_t human = get_random_human();
        add_human(book, human);
    }
}

void init_phonebook(phonebook_t *book){
    book->humans = NULL;
    book->size = 0, book->capacity = 0;
}

void clear_phonebook(phonebook_t *book){
    if (book->humans)
        free(book->humans);
    book->humans = NULL;
    book->size = 0, book->capacity = 0;
}

human_t get_human(phonebook_t *book, char* family_name){
    int i;

    for (i = 0; i < book->size; i++){
        human_t *pointer = &(book->humans[i]);
        if (strcmp(family_name, pointer->family_name) == 0)
            return *pointer;
        pointer++;
    }
    printf("There is no such a human with family name %s in book\n", family_name);
}
