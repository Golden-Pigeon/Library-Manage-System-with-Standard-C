//
// Created by 86133 on 29/5/2020.
//

#ifndef LIBRARY_BOOK_H
#define LIBRARY_BOOK_H

#include <stdbool.h>

typedef struct BOOK{
    char* title;
    char* ISBN;
    int id;
} Book;

Book* creat_book(char* title, char* ISBN);

bool equals(Book* book1, Book* book2);

void print_book(Book* book);

void* free_book(Book* book);

#endif //LIBRARY_BOOK_H
