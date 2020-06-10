//
// Created by 86133 on 2/6/2020.
//

#include <stdlib.h>
#include <string.h>

#include "user.h"

User* create_user(char* name, char* id, UserType ut, char* account, char* password){
    User* user = (User*)malloc(sizeof(User));
    user->name = name;
    user->id = id;
    user->ut = ut;
    user->account = account;
    user->password = password;
    user->borrowed_books = create_book_list();
    return user;
}

User* copy_user(User* user){
    User* u = (User*)malloc(sizeof(User));
    u->name = user->name;
    u->id = user->id;
    u->ut = user->ut;
    u->account = user->account;
    u->password = user->password;
    u->borrowed_books = create_book_list();
    return u;
}

char* get_id(){
    int LEN = 10;
    char* code = (char*)calloc(LEN + 1, sizeof(char));
    for(int i = 0; i < LEN; i++){
        code[i] = rand()%('9' - '0' + 1) + '0';
    }
    code[LEN] = '\0';
    return code;
}

bool is_guest(User* user){
    if(user->ut == GUEST)
        return true;
    return false;
}

bool is_admin(User* user){
    if(user->ut == ADMIN)
        return true;
    return false;
}

bool user_equals(User* u1, User* u2){
    if(strcmp(u1->name, u2->name) == 0 && strcmp(u1->id, u2->id) == 0){
        return true;
    }
    return false;
}

bool account_match(User* user, char* account, char* password){
    if(strcmp(user->account, account) == 0 && strcmp(user->password, password) == 0){
        return true;
    }
    return false;
}

void free_user(User* user){
    free(user->password);
    free(user->account);
    free(user->id);
    free(user->name);
    free(user->borrowed_books);
    free(user);
}

