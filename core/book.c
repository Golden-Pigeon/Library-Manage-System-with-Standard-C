//
// Created by 86133 on 2/6/2020.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "book.h"

Book* creat_book(char* title, char* ISBN){
    static int cnt = 0;
    Book* book = (Book*)malloc(sizeof(Book));
    book->ISBN = ISBN;
    book->title = title;
    book->id = cnt++;
    return book;
}

bool equals(Book* book1, Book* book2){
    if(strcmp(book1->title, book2->title) == 0 && strcmp(book1->ISBN, book2->ISBN) == 0){
        return true;
    }
    return false;
}

void print_book(Book* book){
    printf("%d\t%s\t%s\t", book->id, book->title, book->ISBN);
}

void* free_book(Book* book){
    free(book->ISBN);
    free(book->title);
    free(book);
}

