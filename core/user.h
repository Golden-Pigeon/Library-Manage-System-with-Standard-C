//
// Created by 86133 on 29/5/2020.
//

#ifndef LIBRARY_USER_H
#define LIBRARY_USER_H

#include "../util/list_book.h"

#define DEFAULT_CAP 16

typedef enum USER_TYPE{
    ADMIN, STUDENT, GUEST
} UserType;

static UserType current_user_type = GUEST;

typedef struct USER{
    char* name;
    char* id;
    UserType ut;
    char* account;
    char* password;
    BookList* borrowed_books;
} User;


User* create_user(char* name, char* id, UserType ut, char* account, char* password);

User* copy_user(User* user);

char* get_id();

bool is_guest(User* user);

bool is_admin(User* user);

bool user_equals(User* u1, User* u2);

bool account_match(User* user, char* account, char* password);

void free_user(User* user);

#endif //LIBRARY_USER_H
