//
// Created by 86133 on 29/5/2020.
//

#ifndef LIBRARY_LBR_H
#define LIBRARY_LBR_H

#include "../util/list_user.h"
#include "../util/list_book.h"
#include "../util/hash_map.h"

#define TOTAL -1

typedef struct LIBRARY{
    UserList* userList;
    HashMapBookToInfo* map;
} Library;

Library* create_library();

/**
 * if there are no such book, then create a new item
 * @param book
 * @param amount
 */
void add_books(Library* lbr, Book* book, int amount);

/**
 * delete certain amount of books
 * @param book the book that need to delete
 * @param amount if equals to TOTAL, then delete all books as it can
 */
bool del_books(Library* lbr, Book* book);

/**
 *
 * @param user user that is borrowing books
 * @param book_list books to be borrowed
 * @param ... int type, refers to the amount of each books
 * @return if is successful
 */
bool borrow_books(Library* lbr, User* user, Book* book, int amount);

bool return_books(Library* lbr, User* user, Book* book, int amount);

void return_all(Library* lbr, User* user);

HashMapBookToInfo* search_book_by_id(Library* lbr, int id);

Book* get_book_by_id(Library* lbr, int id);

HashMapBookToInfo* search_book_by_name(Library* lbr, char* pattern);

User* login(Library* lbr, char* account, char* password);

bool reg(Library* lbr, char* name, char* id, UserType ut, char* account, char* password);

bool delete_user(Library* lbr, User* user);

User* get_user_by_id(Library* lbr, char* id);

void free_library(Library* lbr);

#endif //LIBRARY_LBR_H
