#include <expat.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "../include/phonebook.h"

int main(int argc, char **argv) {
    srand(time(NULL));
    if (argc != 3){
        printf("Wrong call format, try again\n");
        return 0;
    }
    phonebook_t book;
    init_phonebook(&book);
    load_phonebook_xml(argv[1], &book);
    print_phonebook(&book);
    gen_phonebook(&book, book.size);
    save_phonebook_xml(argv[2], &book);
    clear_phonebook(&book);
    return 0;
}
