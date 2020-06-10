//
// Created by 86133 on 2/6/2020.
//

#include <string.h>
#include <stdlib.h>

#include "list_book.h"
#include "list_user.h"
#include "my_string.h"

BookNode* create_book_node(Book* book, char* book_code, BookNode* next){
    BookNode* node = (BookNode*)malloc(sizeof(BookNode));
    node->next = next;
    node->book = book;
    node->book_code = book_code;
    return node;
}

void free_book_node(BookNode* node){
    free(node->book_code);
    free_book(node->book);
    free(node);
}

BookList* create_book_list(){
    BookList* list = (BookList*)malloc(sizeof(BookList));
    list->head = NULL;
    return list;
}

void list_add_book(BookList* bl, Book* book, char* book_code){
    if(bl->head == NULL){
        bl->head = create_book_node(book, book_code, NULL);
    }
    else{
        BookNode* n = create_book_node(book, book_code, bl->head);
        bl->head = n;
    }
}

char* list_book_change(BookList* bl, Book* ori, Book* obj, char* book_code){
    if(bl->head == NULL){
        return NULL;
    }
    BookNode* ite = bl->head;
    while(ite){
        if(equals(ite->book, ori)){
            char* old = ite->book_code;
            free(ite->book);
            ite->book = obj;
            ite->book_code = book_code;
            return old;
        }
        ite = ite->next;
    }
    return NULL;
}

bool list_contains_book(BookList* bl, Book* book){
    if(bl->head == NULL){
        return false;
    }
    BookNode* ite = bl->head;
    while(ite){
        if(equals(ite->book, book)){
            return true;
        }
        ite = ite->next;
    }
    return false;
}

char* list_remove_book(BookList* bl, Book* book){
    BookNode* last = bl->head;
    if(last == NULL){
        return NULL;
    }
    if(equals(last->book, book)){
        bl->head = last->next;
        char* old = copy(last->book_code);
        free_book_node(last);
        return old;
    }
    for(BookNode* n = last; n != NULL; n = n->next){
        if(equals(n->book, book)){
            last->next = n->next;
            char* old = copy(n->book_code);
            free_book_node(n);
            return old;
        }
    }
    return NULL;
}

int list_get_book_amount(BookList* bl, Book* book){
    if(bl->head == NULL)
        return 0;
    BookNode* node = bl->head;
    int cnt = 0;
    while(node){
        if(equals(node->book, book))
            cnt++;
        node = node->next;
    }
    return cnt;
}

int list_book_size(BookList* bl){
    if(bl->head == NULL)
        return 0;
    int cnt = 0;
    BookNode* n = bl->head;
    while(n){
        cnt++;
        n = n->next;
    }
    return cnt;
}

void free_book_list(BookList* bl){
    if(bl->head != NULL){
        BookNode* temp = bl->head;
        BookNode* n = temp->next;
        while(n){
            free_book_node(temp);
            temp = n;
            n = n->next;
        }
        free_book_node(temp);
    }
    free(bl);
}

UserNode* create_user_node(User* user, UserNode* next){
    UserNode* node = (UserNode*)malloc(sizeof(UserNode));
    node->next = next;
    node->user = user;
    return node;
}

void free_user_node(UserNode* node){
    free_user(node->user);
    free(node);
}

UserList* create_user_list(){
    UserList* list = (UserList*)malloc(sizeof(UserList));
    list->head = NULL;
    return list;
}

void list_add_user(UserList* ul, User* user){
    if(ul->head == NULL){
        ul->head = create_user_node(user, NULL);
    }
    else{
        UserNode* n = create_user_node(user, ul->head);
        ul->head = n;
    }
}

bool list_user_change(UserList* ul, User* ori, User* obj){
    if(ul->head == NULL){
        return false;
    }
    UserNode* ite = ul->head;
    while(ite){
        if(user_equals(ite->user, ori)){
            free(ite->user);
            ite->user = obj;
            return true;
        }
        ite = ite->next;
    }
    return false;
}

bool list_contains_user(UserList* ul, User* user){
    if(ul->head == NULL){
        return false;
    }
    UserNode* ite = ul->head;
    while(ite){
        if(user_equals(ite->user, user)){
            return true;
        }
        ite = ite->next;
    }
    return false;
}

bool list_remove_user(UserList* ul, User* user){
    UserNode* last = ul->head;
    if(last == NULL){
        return false;
    }
    if(user_equals(last->user, user)){
        ul->head = last->next;
        free_user_node(last);
        return true;
    }
    for(UserNode* n = last; n != NULL; n = n->next){
        if(user_equals(n->user, user)){
            last->next = n->next;
            free_user_node(n);
            return true;
        }
    }
    return false;
}

void free_user_list(UserList* ul){
    if(ul->head != NULL){
        UserNode* temp = ul->head;
        UserNode* n = temp->next;
        while(n){
            free_user_node(temp);
            temp = n;
            n = n->next;
        }
        free_user_node(temp);
    }
    free(ul);
}