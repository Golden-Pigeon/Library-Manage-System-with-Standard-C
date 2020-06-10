//
// Created by 86133 on 3/6/2020.
//

#ifndef LIBRARY_LIST_USER_H
#define LIBRARY_LIST_USER_H

#include "stdbool.h"

#include "../core/user.h"

typedef struct USER_NODE{
    User* user;
    struct USER_NODE* next;
} UserNode;

UserNode* create_user_node(User* user, UserNode* next);

void free_user_node(UserNode* node);

typedef struct USER_LIST{
    UserNode* head;
} UserList;

UserList* create_user_list();

void list_add_user(UserList* ul, User* user);

bool list_user_change(UserList* ul, User* ori, User* obj);

bool list_contains_user(UserList* ul, User* user);

bool list_remove_user(UserList* ul, User* user);

void free_user_list(UserList* ul);


#endif //LIBRARY_LIST_USER_H
