//
// Created by 86133 on 29/5/2020.
//

#ifndef LIBRARY_HASH_H
#define LIBRARY_HASH_H

#include <stdint.h>
#include "../core/book.h"

uint64_t hash_s(char* str);

uint64_t hash_book(Book* book);

#endif //LIBRARY_HASH_H
