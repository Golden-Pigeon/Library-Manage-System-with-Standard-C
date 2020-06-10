//
// Created by 86133 on 29/5/2020.
//

#ifndef LIBRARY_HASH_MAP_H
#define LIBRARY_HASH_MAP_H

#include <stdbool.h>

#include "../core/user.h"
#include "../core/book.h"

typedef struct HASH_NODE_BOOK_CODE_TO_USER{
    char* code;
    User* user;
    struct HASH_NODE_BOOK_CODE_TO_USER* next;
} HashNodeBookCodeToUser;

HashNodeBookCodeToUser* create_hash_node_ctu(char* code, User* user, HashNodeBookCodeToUser* next);

char* get_code();

void free_node_ctu(HashNodeBookCodeToUser* node);

typedef struct HASH_MAP_BOOK_CODE_TO_USER{
    int capacity;
    double load_factor;
    int size;
    HashNodeBookCodeToUser** table;
} HashMapBookCodeToUser;

HashMapBookCodeToUser* create_hash_map_ctu(int cap, double load_factor);

User* put_ctu(HashMapBookCodeToUser* map, char* key, User* value);

User* get_ctu(HashMapBookCodeToUser* map, char* key);

User* remove_ctu(HashMapBookCodeToUser* map, char* key);

bool key_contains_ctu(HashMapBookCodeToUser* map, char* key);

bool grow_ctu(HashMapBookCodeToUser* map);

void free_map_ctu(HashMapBookCodeToUser* map);

int map_ctu_size(HashMapBookCodeToUser* map);

typedef struct INFO{
    int total_amount;
    int current_amount;
    HashMapBookCodeToUser* map;
} Info;

Info* create_info(int total, int current, HashMapBookCodeToUser* map);

void add_books_info(Info* info, int amount);

char* get_avai_code(Info* info);

Info* copy_info(Info* info);

void free_info(Info* info);

typedef struct HASH_NODE_BOOK_TO_INFO{
    Book* book;
    Info* info;
    struct HASH_NODE_BOOK_TO_INFO* next;
} HashNodeBookToInfo;

HashNodeBookToInfo* create_hash_node_bti(Book* book, Info* info, HashNodeBookToInfo* next);

void free_node_bti(HashNodeBookToInfo* node);

typedef struct HASH_MAP_BOOK_TO_INFO{
    int capacity;
    double load_factor;
    int size;
    HashNodeBookToInfo** table;
} HashMapBookToInfo;

HashMapBookToInfo* create_hash_map_bti(int cap, double load_factor);

Info* put_bti(HashMapBookToInfo * map, Book* key, Info* value);

Info* get_bti(HashMapBookToInfo* map, Book* key);

Info* remove_bti(HashMapBookToInfo* map, Book* key);

bool key_contains_bti(HashMapBookToInfo* map, Book* key);

bool grow_bti(HashMapBookToInfo* map);

void free_map_bti(HashMapBookToInfo* map);

#endif //LIBRARY_HASH_MAP_H
