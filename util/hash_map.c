//
// Created by 86133 on 2/6/2020.
//

/**
 * need recode to fit the "lbr.h"  3/6/2020 3:44 p.m.
 */


#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "hash_map.h"
#include "hash.h"
#include "my_math.h"



HashNodeBookCodeToUser* create_hash_node_ctu(char* code, User* user, HashNodeBookCodeToUser* next){
    HashNodeBookCodeToUser* node = (HashNodeBookCodeToUser*)malloc(sizeof(HashNodeBookCodeToUser));
    if(code == NULL){
        return NULL;
    }
    node->code = code;
    node->user = user;
    node->next = next;
    return node;
}

char* get_code(){
    int LEN = 10;
//  srand(time(NULL));
    char* code = (char*)calloc(LEN + 1, sizeof(char));
    for(int i = 0; i < LEN; i++){
        code[i] = rand()%('z' - 'a' + 1) + 'a';
    }
    code[LEN] = '\0';
    return code;
}


void free_node_ctu(HashNodeBookCodeToUser* node){
    free(node->code);
    free(node->user);
    free(node);
}

HashMapBookCodeToUser* create_hash_map_ctu(int cap, double load_factor){
    HashMapBookCodeToUser* map = (HashMapBookCodeToUser*)malloc(sizeof(HashMapBookToInfo));
    map->load_factor = load_factor;
    map->size = 0;
    if(cap <= DEFAULT_CAP)
        map->capacity = DEFAULT_CAP;
    else {
        for(int i = 4;;i++) {
            if(my_pow(2, i) < cap && cap <= my_pow(2, i + 1)){
                map->capacity = my_pow(2, i + 1);
                break;
            }
        }
    }
    map->table = (HashNodeBookCodeToUser**)calloc(map->capacity, sizeof(HashNodeBookCodeToUser*));
    memset(map->table, 0, map->capacity * sizeof(HashNodeBookCodeToUser*));
    return map;
}

User* put_ctu(HashMapBookCodeToUser* map, char* key, User* value){

    typedef HashNodeBookCodeToUser Node;
    typedef HashMapBookCodeToUser Map;
    grow_ctu(map);
    uint64_t hash = hash_s(key);
    int index = (int)(hash % (uint64_t)map->capacity);
    for(Node* n = map->table[index]; n != NULL; n = n->next){
        if(strcmp(key, n->code) == 0){
            User* old = n->user;
            n->user = value;
            return old;
        }
    }

    Node* node = create_hash_node_ctu(key, value, map->table[index]);
    map->table[index] = node;
    map->size++;
    return NULL;
}

User* get_ctu(HashMapBookCodeToUser* map, char* key){
    typedef HashNodeBookCodeToUser Node;
    typedef HashMapBookCodeToUser Map;
    if(key == NULL){
        return NULL;
    }
    uint64_t hash = hash_s(key);
    int index = (int)(hash % (uint64_t)map->capacity);
    for(Node* n = map->table[index]; n != NULL; n = n->next){
        if(strcmp(key, n->code) == 0){
            return n->user;
        }
    }

    return NULL;

}

User* remove_ctu(HashMapBookCodeToUser* map, char* key){
    typedef HashNodeBookCodeToUser Node;
    typedef HashMapBookCodeToUser Map;
    uint64_t hash = hash_s(key);
    int index = (int)(hash % (uint64_t)map->capacity);
    Node* last = map->table[index];
    if(last == NULL){
        return NULL;
    }
    if(strcmp(last->code, key) == 0){
        User* old = copy_user(last->user);
        free_node_ctu(last);
        map->table[index] = map->table[index]->next;
        return old;
    }
    for(Node* n = map->table[index]; n != NULL; n = n->next){
        if(strcmp(key, n->code) == 0){
            last->next = n->next;
            User* old = copy_user(n->user);
            free_node_ctu(n);
            return old;
        }
        last = n;
    }
    return NULL;
}

bool key_contains_ctu(HashMapBookCodeToUser* map, char* key){
    typedef HashNodeBookCodeToUser Node;
    uint64_t hash = hash_s(key);
    int index = (int)(hash % (uint64_t)map->capacity);
    for(Node* n = map->table[index]; n != NULL; n = n->next){
        if(strcmp(key, n->code) == 0){
            return true;
        }
    }
    return false;

}

bool grow_ctu(HashMapBookCodeToUser* map){
    typedef HashNodeBookCodeToUser Node;
    int threshold = (int)(map->load_factor * map->capacity);
    if(map->size < threshold)
        return true;
    Node** old = map->table;
    int cap_old = map->capacity;
    map->capacity *= 2;
    map->table = (Node**)calloc(map->capacity, sizeof(Node*));
    map->size = 0;
    memset(map->table, 0, map->capacity * sizeof(Node*));
    for(int i = 0; i < cap_old; i++){
        for(Node* n = old[i]; n != NULL; n = n->next){
            put_ctu(map, n->code, n->user);
        }
    }
    return true;

}

void free_map_ctu(HashMapBookCodeToUser* map){
    typedef HashNodeBookCodeToUser Node;
    for(int i = 0; i < map->capacity; i++){
        if(map->table[i] == NULL){
            continue;
        }
        Node* temp = map->table[i];
        Node* n = temp->next;
        while(n){
            free_node_ctu(temp);
            temp = n;
            n = n->next;
        }
        free_node_ctu(temp);
    }
    free(map->table);
    free(map);

}

int map_ctu_size(HashMapBookCodeToUser* map){
    return map->size;
}

Info* create_info(int total, int current, HashMapBookCodeToUser* map){
    Info* info = (Info*)malloc(sizeof(Info));
    info->current_amount = current;
    info->total_amount = total;
    info->map = map;
    if(map->size < current){
        int n = current - map->size;
        for(int i = 0; i < n; i++){
            char* code = get_code();
            put_ctu(info->map, code, NULL);
        }
    }
    return info;
}

void add_books_info(Info* info, int amount){
    info->current_amount += amount;
    info->total_amount += amount;
    srand(time(NULL));
    for(int i = 0; i < amount; i++){
        char* code = get_code();
        put_ctu(info->map, code, NULL);
    }
    return;
}

char* get_avai_code(Info* info){
    HashMapBookCodeToUser* map = info->map;
    typedef HashNodeBookCodeToUser Node;
    for(int i = 0; i < map->capacity; i++){
        if(map->table[i] == NULL){
            continue;
        }
        Node* n = map->table[i];
        while(n){
            if(n->user == NULL)
                return n->code;
            n = n->next;
        }
    }
    return NULL;
}

Info* copy_info(Info* info){
    Info* n = (Info*)malloc(sizeof(Info));
    n->map = info->map;
    n->total_amount = info->total_amount;
    n->current_amount = info->current_amount;
    return n;
}

void free_info(Info* info){
    free_map_ctu(info->map);
    free(info);
}

HashNodeBookToInfo* create_hash_node_bti(Book* book, Info* info, HashNodeBookToInfo* next){
    typedef HashNodeBookToInfo Node;
    Node* node = (Node*)malloc(sizeof(Node));
    node->info = info;
    node->book = book;
    node->next = next;
    return node;
}

void free_node_bti(HashNodeBookToInfo* node){
    free_book(node->book);
    free_info(node->info);
    free(node);
}

HashMapBookToInfo* create_hash_map_bti(int cap, double load_factor){
    typedef HashMapBookToInfo Map;
    typedef HashNodeBookToInfo Node;
    Map* map = (Map*)malloc(sizeof(Map));
    map->load_factor = load_factor;
    map->size = 0;
    if(cap <= DEFAULT_CAP)
        map->capacity = DEFAULT_CAP;
    else {
        for(int i = 4;;i++) {
            if(my_pow(2, i) < cap && cap <= my_pow(2, i + 1)){
                map->capacity = my_pow(2, i + 1);
                break;
            }
        }
    }
    map->table = (Node**)calloc(map->capacity, sizeof(Node*));
    memset(map->table, 0, map->capacity * sizeof(Node*));
    return map;
}

Info* put_bti(HashMapBookToInfo * map, Book* key, Info* value){
    typedef HashNodeBookToInfo Node;
    grow_bti(map);
    uint64_t hash = hash_book(key);
    int index = (int)(hash % (uint64_t)map->capacity);
    for(Node* n = map->table[index]; n != NULL; n = n->next){
        if(equals(key, n->book)){
            Info* old = n->info;
            n->info = value;
            return old;
        }
    }

    Node* node = create_hash_node_bti(key, value, map->table[index]);
    map->table[index] = node;
    map->size++;
    return NULL;
}

Info* get_bti(HashMapBookToInfo* map, Book* key){
    typedef HashNodeBookToInfo Node;
    if(key == NULL)
        return NULL;
    uint64_t hash = hash_book(key);
    int index = (int)(hash % (uint64_t)map->capacity);
    for(Node* n = map->table[index]; n != NULL; n = n->next){
        if(equals(key, n->book)){
            return n->info;
        }
    }

    return NULL;
}

Info* remove_bti(HashMapBookToInfo* map, Book* key){
    typedef HashNodeBookToInfo Node;
    uint64_t hash = hash_book(key);
    int index = (int)(hash % (uint64_t)map->capacity);
    Node* last = map->table[index];
    if(last == NULL){
        return NULL;
    }
    if(equals(last->book, key)){
        Info* old = copy_info(last->info);
        free_node_bti(last);
        map->table[index] = map->table[index]->next;
        return old;
    }
    for(Node* n = map->table[index]; n != NULL; n = n->next){
        if(equals(key, n->book)){
            last->next = n->next;
            Info* old = copy_info(last->info);
            free_node_bti(n);
            return old;
        }
        last = n;
    }
    return NULL;
}

bool key_contains_bti(HashMapBookToInfo* map, Book* key){
    typedef HashNodeBookToInfo Node;
    uint64_t hash = hash_book(key);
    int index = (int)(hash % (uint64_t)map->capacity);
    for(Node* n = map->table[index]; n != NULL; n = n->next){
        if(equals(key, n->book)){
            return true;
        }
    }

    return false;
}

bool grow_bti(HashMapBookToInfo* map){
    typedef HashNodeBookToInfo Node;
    int threshold = (int)(map->load_factor * map->capacity);
    if(map->size < threshold)
        return true;
    Node** old = map->table;
    int cap_old = map->capacity;
    map->capacity *= 2;
    map->table = (Node**)calloc(map->capacity, sizeof(Node*));
    map->size = 0;
    memset(map->table, 0, map->capacity * sizeof(Node*));
    for(int i = 0; i < cap_old; i++){
        for(Node* n = old[i]; n != NULL; n = n->next){
            put_bti(map, n->book, n->info);
        }
    }
    return true;
}

void free_map_bti(HashMapBookToInfo* map){
    typedef HashNodeBookToInfo Node;
    for(int i = 0; i < map->capacity; i++){
        if(map->table[i] == NULL){
            continue;
        }
        Node* temp = map->table[i];
        Node* n = temp->next;
        while(n){
            free_node_bti(temp);
            temp = n;
            n = n->next;
        }
        free_node_bti(temp);
    }
    free(map->table);
    free(map);
}