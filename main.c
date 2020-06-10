#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#include "main.h"
#include "util/my_string.h"

Library* lbr = NULL;
User* current_user = NULL;


void initialize(){
    lbr = create_library();
    add_books(lbr, creat_book("C_and_Pointer", "1-1234-123-11"), 10);
    add_books(lbr, creat_book("Half_Life_3", "1-4321-123-11"), 20);
    add_books(lbr, creat_book("C_Primer_Plus", "1-1234-321-11"), 20);
    add_books(lbr, creat_book("Thinking_in_C++", "1-1234-123-22"), 20);
    add_books(lbr, creat_book("Core_Java", "1-1324-123-11"), 20);
    reg(lbr, copy("admin"), copy("001"), ADMIN, copy("admin"), copy("******"));
}

void end(){
    free_library(lbr);
    exit(0);
}

void main_menu(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(true) {
        system("cls");
        puts("\xDA-------------------\xBF");
        puts("\xB3     MAIN_MENU     \xB3");
        puts("\xB3  1.login          \xB3");
        puts("\xB3  2.signup         \xB3");
        puts("\xB3  3.login as guest \xB3");
        puts("\xB3  4.quit           \xB3");
        puts("\xC0-------------------\xD9");
        puts("\ninput your option(automatically ignore redundant input):");
        int ch = getchar();
        int c;
        while ((c = getchar()) != '\n');
        switch (ch) {
            case '1':
                log_in();
                break;
            case '2':
                sign_up();
                break;
            case '3':
                guest_menu();
                break;
            case '4':
                end();
                break;
            default:
                puts("unknown command");
                system("pause"); getchar();
                break;
        }
    }
#pragma clang diagnostic pop
}

void sign_up(){
    char account[101];
    char* password;
    char* confirm;
    char* id;
    char name[100];
    while(true) {
        system("cls");
        puts("sign up interface");
        puts("please input your name(in 100 chars, the same below):");
        scanf("%s", name);
        puts("please input your account:");
        scanf("%s", account);
        puts("please input your password:");
        password = get_password(100);
        puts("please input again to confirm:");
        confirm = get_password(100);
        if (strcmp(password, confirm) == 0) {
            id = get_id();
            if (reg(lbr, copy(name), id, STUDENT, copy(account), password)) {
                puts("sign in successfully!");
                system("pause"); getchar();
                break;
            }
            else {
                puts("account info has existed");
                free(confirm);
                free(password);
                break;
            }
        }
        else{
            puts("the two passwords are different");
            free(confirm);
            free(password);
            system("pause"); getchar();
        }
    }


}

void log_in(){
    char account[101];
    char* password;
    puts("please input your account(in 100 chars):");
    scanf("%s", account);
    puts("please input your password");
    password = get_password(100);
    current_user = login(lbr, account, password);
    if(current_user != NULL){
        puts("login successfully!");
        
        system("pause"); getchar();
        if(is_admin(current_user)) {
            current_user_type = ADMIN;
            admin_menu();
        }
        else{
            current_user_type = STUDENT;
            student_menu();
        }
    }
    else{
        puts("login failed.");
        system("pause"); getchar();
    }
}

void guest_menu(){
    while(true) {
        system("cls");
        puts("\xDA-------------------\xBF");
        puts("\xB3     GUEST_MENU    \xB3");
        puts("\xB3  1.search book    \xB3");
        puts("\xB3  2.quit           \xB3");
        puts("\xC0-------------------\xD9");
        puts("\ninput your option(automatically ignore redundant input):");
        int ch = getchar();
        while (getchar() != '\n');
        switch (ch) {
            case '1':
                search_book();
                break;
            case '2':
                current_user = NULL;
                return;
            default:
                puts("unknown command");
                system("pause"); getchar();
                break;
        }
    }
}

void admin_menu(){
    while(true) {
        system("cls");
        puts("\xDA-------------------\xBF");
        puts("\xB3     ADMIN_MENU    \xB3");
        puts("\xB3  1.search stu     \xB3");
        puts("\xB3  2.search book    \xB3");
        puts("\xB3  3.add books      \xB3");
        puts("\xB3  4.delete books   \xB3");
        puts("\xB3  5.borrow books   \xB3");
        puts("\xB3  6.return books   \xB3");
        puts("\xB3  7.edit stu info  \xB3");
        puts("\xB3  8.quit           \xB3");
        puts("\xC0-------------------\xD9");
        puts("\ninput your option(automatically ignore redundant input):");
        int ch = getchar();
        while (getchar() != '\n');
        system("cls");
        switch (ch) {
            case '1':
                search_stu();
                break;
            case '2':
                search_book();
                break;
            case '3': {
                puts("input [title] [ISBN] [amount]");
                char title[100];
                char ISBN[100];
                int amount;
                scanf("%s%s%d", title, ISBN, &amount);
                Book *book = creat_book(title, ISBN);
                add_books(lbr, book, amount);
                puts("success!");
                system("pause"); getchar();
            }
                break;
            case '4': {
                puts("input [id]");
                int id;
                scanf("%d", &id);
                Book *book = get_book_by_id(lbr, id);
                if (book == NULL) {
                    puts("no such book in library");
                    system("pause"); getchar();
                    break;
                }
                if (del_books(lbr, book))
                    puts("success!");
                else
                    puts("failed.\nsomeone is still borrowing");
            }
                system("pause"); getchar();
                break;
            case '5': {
                int book_id, amount;
                char user_id[100];
                puts("input [user_id] [book_id] [amount]");
                scanf("%s%d%d", user_id, &book_id, &amount);
                User* user = get_user_by_id(lbr, user_id);
                if(user == NULL){
                    puts("no such user");
                    system("pause"); getchar();
                    break;
                }
                Book* book = get_book_by_id(lbr, book_id);
                if(book == NULL){
                    puts("no such book");
                    system("pause"); getchar();
                    break;
                }
                if(borrow_books(lbr, user, book, amount)){
                    puts("success!");
                }
                else{
                    puts("failed.");
                    puts("no enough books");
                }
            }
                system("pause"); getchar();
                break;
            case '6':{
                int book_id, amount;
                char user_id[100];
                puts("input [user_id] [book_id] [amount]");
                scanf("%s%d%d", user_id, &book_id, &amount);
                User* user = get_user_by_id(lbr, user_id);
                if(user == NULL){
                    puts("no such user");
                    system("pause"); getchar();
                    break;
                }
                if(amount < 0){
                    return_all(lbr, user);
                    puts("success!");
                    system("pause"); getchar();
                    break;
                }
                Book* book = get_book_by_id(lbr, book_id);
                if(book == NULL){
                    puts("no such book");
                    system("pause"); getchar();
                    break;
                }
                if(return_books(lbr, user, book, amount)){
                    puts("success!");
                }
                else{
                    puts("failed.");
                    puts("no enough books");
                }
                system("pause"); getchar();

            }
                break;
            case '7':
                puts("input [user_id]");
                char user_id[100];
                scanf("%s", user_id);
                User* user = get_user_by_id(lbr, user_id);
                if(user == NULL){
                    puts("no such user");
                    system("pause"); getchar();
                    break;
                }
                puts("the original info is\nname\tid\ttype\taccount\tpassword");
                printf("%s\t%s\t%d\t%s\t%s\n", user->name, user->id, user->ut, user->account, user->password);
                puts("you can input the new [name] [password]");
                char name[100], pw[100];
                scanf("%s%s", name, pw);
                free(user->name);
                free(user->password);
                user->name = copy(name);
                user->password = copy(pw);
                puts("success!");
                system("pause"); getchar();
                break;
            case '8':
                current_user = NULL;
                current_user_type = GUEST;
                return;
            default:
                puts("unknown command");
                system("pause"); getchar();
                break;
        }
    }
}

void student_menu(){
    while(true){
        system("cls");
        puts("\xDA-------------------\xBF");
        puts("\xB3      STU_MENU     \xB3");
        puts("\xB3  1.your info      \xB3");
        puts("\xB3  2.search book    \xB3");
        puts("\xB3  3.borrow books   \xB3");
        puts("\xB3  4.return books   \xB3");
        puts("\xB3  5.quit           \xB3");
        puts("\xC0-------------------\xD9");
        puts("\ninput your option(automatically ignore redundant input):");

        int ch = getchar();
        while (getchar() != '\n');
        system("cls");
        switch (ch) {
            case '1':
                search_stu();
                break;
            case '2':
                search_book();
                break;
            case '3':{
                int book_id, amount;
                puts("input [book_id] [amount]");
                scanf("%d%d", &book_id, &amount);
                Book* book = get_book_by_id(lbr, book_id);
                if(book == NULL){
                    puts("no such book");
                    system("pause"); getchar();
                    break;
                }
                if(borrow_books(lbr, current_user, book, amount)){
                    puts("success!");
                }
                else{
                    puts("failed.");
                    puts("no enough books");
                }
            }
                system("pause"); getchar();
                break;
            case '4':{
                int book_id, amount;
                puts("input [book_id] [amount]");
                scanf("%d%d", &book_id, &amount);
                if(amount < 0){
                    return_all(lbr, current_user);
                    puts("success!");
                    system("pause"); getchar();
                    break;
                }
                Book* book = get_book_by_id(lbr, book_id);
                if(book == NULL){
                    puts("no such book");
                    system("pause"); getchar();
                    break;
                }
                if(return_books(lbr, current_user, book, amount)){
                    puts("success!");
                }
                else{
                    puts("failed.");
                    puts("no enough books");
                }
                system("pause"); getchar();

            }

                break;
            case '5':
                return;
            default:
                puts("unknown command");
                system("pause"); getchar();
                break;
        }
    }
}

void search_book(){
    system("cls");
    puts("\xDA-------------------\xBF");
    puts("\xB3    SEARCH_MENU    \xB3");
    puts("\xB3  1.id             \xB3");
    puts("\xB3  2.title          \xB3");
    puts("\xC0-------------------\xD9");
    puts("\ninput your option(automatically ignore redundant input):");
    int ch = getchar();
    while (getchar() != '\n');
    system("cls");
    switch (ch) {
        case '1':{
            int id;
            puts("input [id]");
            scanf("%d", &id);
            Book* book = get_book_by_id(lbr, id);
            Info* info = get_bti(lbr->map, book);
            if(info == NULL){
                puts("not found");
                break;
            }
            puts("id\ttitle\tISBN\ttotal\tcurrent");
            printf("%d\t%s\t%s\t%d\t%d\n", book->id, book->title, book->ISBN, info->total_amount, info->current_amount);
            if(current_user_type == ADMIN){
                puts("code\tstatus");
                for(int i = 0; i < info->map->capacity; i++){
                    for(HashNodeBookCodeToUser* n = info->map->table[i]; n != NULL; n = n->next){
                        if(n->user == NULL){
                            printf("%s\tin stock\n", n->code);
                        }
                        else{
                            printf("%s\t%s\n", n->code, n->user->id);
                        }
                    }
                }

            }
        }

            break;
        case '2': {
            HashMapBookToInfo *map;
            bool total = false;
            char title[100];
            puts("input [title]");
            scanf("%s", title);
            if(strcmp(title, ".") == 0){
                map = lbr->map;
                total = true;
            }
            else{
                map = search_book_by_name(lbr, title);
            }
            if(map->size == 0){
                puts("not found");
            }
            int cnt = 0;
            puts("id\ttitle\tISBN\ttotal\tcurrent");
            for(int i = 0; i < map->capacity; i++){
                for(HashNodeBookToInfo* node = map->table[i]; node != NULL; node = node->next){
                    Book* book = node->book;
                    Info* info = node->info;
                    if(cnt > 0 && current_user_type == ADMIN)
                        puts("id\ttitle\tISBN\ttotal\tcurrent");
                    cnt++;
                    printf("%d\t%s\t%s\t%d\t%d\n", book->id, book->title, book->ISBN, info->total_amount, info->current_amount);
                    if(current_user_type == ADMIN){
                        puts("code\tstatus");
                        for(int j = 0; j < info->map->capacity; j++){
                            for(HashNodeBookCodeToUser* n = info->map->table[j]; n != NULL; n = n->next){
                                if(n->user == NULL){
                                    printf("%s\tin stock\n", n->code);
                                }
                                else{
                                    printf("%s\t%s\n", n->code, n->user->id);
                                }
                            }
                        }

                    }
                }
            }

            if(!total)
                free(map);
        }
            break;
        default:
            puts("unknown command");

            break;
    }
    system("pause"); getchar();
}

void search_stu(){
    system("cls");
    char id[100];
    User* user;
    if(current_user_type == ADMIN){
        puts("input [id]");
        scanf("%s", id);
        user = get_user_by_id(lbr, id);
        if(user == NULL){
            puts("not found");
            system("pause"); getchar();
            return;
        }
    }
    else if(current_user_type == STUDENT){
        user = current_user;
    }
    else{
        puts("permission denied");
        system("pause"); getchar();
        return;
    }

    puts("name\tid\ttype\t");
    printf("%s\t%s\t%d\n", user->name, user->id, user->ut);
    BookList* list = user->borrowed_books;
    if(list_book_size(list) == 0){
        puts("haven\'t borrowed books\n");
        system("pause"); getchar();
        return;
    }
    puts("book info\nid\ttitle\tISBN\tcode");
    BookNode* node = list->head;
    while(node){
        printf("%d\t%s\t%s\t%s\n", node->book->id, node->book->title, node->book->ISBN, node->book_code);
        node = node->next;
    }
    system("pause"); getchar();
}


int main() {
//    setbuf(stdout, NULL); //use for debug
    system("chcp 437");
    system("cls");
    initialize();
    main_menu();
    return 0;
}
