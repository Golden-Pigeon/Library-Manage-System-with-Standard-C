//
// Created by 86133 on 3/6/2020.
//

#ifndef LIBRARY_LIST_BOOK_H
#define LIBRARY_LIST_BOOK_H

#include "../core/book.h"

typedef struct BOOK_NODE{
    Book* book;
    char* book_code;
    struct BOOK_NODE* next;
} BookNode;

BookNode* create_book_node(Book* book, char* book_code, BookNode* next);

void free_book_node(BookNode* node);

typedef struct BOOK_LIST{
    BookNode* head;
} BookList;

BookList* create_book_list();

void list_add_book(BookList* bl, Book* book, char* book_code);

char* list_book_change(BookList* bl, Book* ori, Book* obj, char* book_code);

bool list_contains_book(BookList* bl, Book* book);

char* list_remove_book(BookList* bl, Book* book);

int list_get_book_amount(BookList* bl, Book* book);

int list_book_size(BookList* bl);

void free_book_list(BookList* bl);



#endif //LIBRARY_LIST_BOOK_H
