//
// Created by 86133 on 3/6/2020.
//

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include "my_string.h"


char* copy(char* str){
    size_t len = strlen(str);
    char* res = (char*)malloc((len + 1) * sizeof(char));
    strcpy(res, str);
    return res;
}

char* get_password(int limit){
    char* pw = (char*)malloc(limit + 1);
    memset(pw, 0, limit + 1);
    scanf("%s", pw);
   // return pw;
 //   strcpy(pw, "******");
 //   return pw;

    int cnt = 0;
    char c;
    while((c = getch()) != '\r'){
        putchar('*');
        fflush(stdin);
        pw[cnt++] = c;
        if(cnt == limit)
            break;
    }
    pw[cnt] = '\0';
    putchar('\n');
    return pw;
}