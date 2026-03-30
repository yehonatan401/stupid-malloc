//
// Created by yehonatan  bondrenko on 3/30/26.
//
#include <stdio.h>

#include "stupid-malloc.h"
int main () {
    int *hi = stupid_malloc(sizeof(int));
    *hi = 5;
    printf("%d",*hi);
    stupid_free(hi);
    if (hi == nullptr) {
        printf("\nhi");
    }else {
        printf("\nfunction work!");
    }
    return 0;
}