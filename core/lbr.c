//
// Created by 86133 on 3/6/2020.
//

#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

#include "lbr.h"

Library* create_library(){
    Library* lbr = (Library*)malloc(sizeof(Library));
    lbr->map = create_hash_map_bti(128, 0.75);
    lbr->userList = create_user_list();
    return lbr;
}

void add_books(Library* lbr, Book* book, int amount){
    Info* info = get_bti(lbr->map, book);
    if(amount < 0)
        return;
    if(info != NULL){
        add_books_info(info, amount);
        return;
    }
    info = create_info(amount, amount, create_hash_map_ctu(128, 0.75));
    put_bti(lbr->map, book, info);
}

bool del_books(Library* lbr, Book* book){
    Info* info = get_bti(lbr->map, book);
    if(info == NULL)
        return false;
    if(info->total_amount != info->current_amount)
        return false;
    remove_bti(lbr->map, book);
    return true;
}

bool borrow_books(Library* lbr, User* user, Book* book, int amount){
    Info* info = get_bti(lbr->map, book);
    if(amount <= 0)
        return false;
    if(info == NULL){
        return false;
    }
    if(!list_contains_user(lbr->userList, user))
        return false;
    if(amount > info->current_amount){
        return false;
    }
    for(int i = 0; i < amount; i++){
        char* code = get_avai_code(info);
        put_ctu(info->map, code, user);
        list_add_book(user->borrowed_books, book, code);
    }
    info->current_amount -= amount;
    return true;
}

bool return_books(Library* lbr, User* user, Book* book, int amount){
    Info* info = get_bti(lbr->map, book);
    if(amount <= 0){
        return false;
    }
    if(info == NULL){
        return false;
    }
    if(!list_contains_user(lbr->userList, user))
        return false;
    if(!list_contains_book(user->borrowed_books, book)){
        return false;
    }
    if (amount > list_get_book_amount(user->borrowed_books, book))
        return false;
    for(int i = 0; i < amount; i++){
        char* code = list_remove_book(user->borrowed_books, book);
        put_ctu(info->map, code, NULL);
        free(code);
    }
    info->current_amount += amount;
    return true;
}

void return_all(Library* lbr, User* user){
    while(true){
        if(list_book_size(user->borrowed_books) == 0)
            break;

        Book* book = user->borrowed_books->head->book;
        int amount = list_get_book_amount(user->borrowed_books, book);
        return_books(lbr, user, book, amount);
    }
}

HashMapBookToInfo* search_book_by_id(Library* lbr, int id){
    typedef HashNodeBookToInfo Node;
    typedef HashMapBookToInfo Map;
    Map* map;
    Info* info;
    for(int i = 0; i < lbr->map->capacity; i++){
        for(Node* n = lbr->map->table[i]; n != NULL; n = n->next){
            if(n->book->id == id) {
                map = create_hash_map_bti(16, 0.75);
                info = get_bti(lbr->map, n->book);
                put_bti(map, n->book, info);
                return map;
            }
        }
    }
    return NULL;
}

Book* get_book_by_id(Library* lbr, int id){
    typedef HashNodeBookToInfo Node;
    Info* info;
    for(int i = 0; i < lbr->map->capacity; i++){
        for(Node* n = lbr->map->table[i]; n != NULL; n = n->next){
            if(n->book->id == id) {
                return n->book;
            }
        }
    }
    return NULL;
}

HashMapBookToInfo* search_book_by_name(Library* lbr, char* pattern){
    typedef HashNodeBookToInfo Node;
    typedef HashMapBookToInfo Map;
    Map* map;
    Info* info;
    map = create_hash_map_bti(16, 0.75);
    for(int i = 0; i < lbr->map->capacity; i++){
        for(Node* n = lbr->map->table[i]; n != NULL; n = n->next){
            if(strstr(n->book->title, pattern)) {
                info = get_bti(lbr->map, n->book);
                put_bti(map, n->book, info);
            }
        }
    }
    return map;
}

User* login(Library* lbr, char* account, char* password){
    UserList* list = lbr->userList;
    if(list->head == NULL)
        return NULL;
    UserNode* node = list->head;
    while(node){
        if(account_match(node->user, account, password))
            return node->user;
        node = node->next;
    }
    return NULL;
}

bool reg(Library* lbr, char* name, char* id, UserType ut, char* account, char* password){
    UserList* list = lbr->userList;
    if(list->head != NULL){
        UserNode* node = list->head;
        while(node){
            if(strcmp(node->user->name, name) == 0 || strcmp(node->user->id, id) == 0 || strcmp(node->user->account, account) == 0)
                return false;
            node = node->next;
        }
    }
    User* user = create_user(name, id, ut, account, password);
    list_add_user(list, user);
    return true;
}

bool delete_user(Library* lbr, User* user){
    UserList* list = lbr->userList;
    if(list->head == NULL)
        return false;
    UserNode* node = list->head;
    while(node){
        if(user_equals(node->user, user)){
            if(list_book_size(user->borrowed_books) == 0){
                list_remove_user(list, user);
                return true;
            }
            return false;

        }
        node = node->next;
    }
    return false;
}

User* get_user_by_id(Library* lbr, char* id){
    UserList* list = lbr->userList;
    if(list->head == NULL)
        return NULL;
    UserNode* node = list->head;
    while(node){
        if(strcmp(node->user->id, id) == 0){
            return node->user;
        }
        node = node->next;
    }
    return NULL;
}

void free_library(Library* lbr){
    free_user_list(lbr->userList);
    free_map_bti(lbr->map);
    free(lbr);
}