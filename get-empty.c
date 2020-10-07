/*
 * list-test1.c -- test function for list.h
 * get() from an empty list
 */
 
#include <stdio.h>
#include <stdint.h>
#include "list.h"

int32_t main() {
    car_t *result;

    result = lget();
    if(result) {
        fprintf(stderr, "Function Error: 'lget()' is not supposed to get from an empty list\n");
        return 1;
    }
    
    return 0;
 }
