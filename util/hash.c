//
// Created by 86133 on 2/6/2020.
//

#include <stdlib.h>

#include "hash.h"

uint64_t hash_s(char* str){
    if(str == NULL)
        return 0;
    uint64_t hash = 5381;

    while (*str)
    {
        hash += (hash << 5) + (*str++);
    }

    return (hash & 0x7FFFFFFFull);
}

uint64_t hash_book(Book* book){
    uint64_t hash = 5381;
    uint64_t hash_title = hash_s(book->title);
    uint64_t hash_ISBN = hash_s(book->ISBN);
    hash += (hash << 5) + (hash_title);
    hash += (hash << 5) + (hash_ISBN);
    return (hash & 0x7FFFFFFFull);
}