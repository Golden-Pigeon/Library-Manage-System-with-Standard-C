//
// Created by 86133 on 2/6/2020.
//

#include "my_math.h"

int my_pow(int a, int b){
    int res = 1;
    while(b){
        res *= a;
        b--;
    }
    return  res;
}
