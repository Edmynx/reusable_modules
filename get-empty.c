/*
 * list-test1.c -- test function for list.h
 * get() from an empty list
 */
 
 #include "list.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int32_t main() {
    car_t *result;

    result = lget();
    if(result) {
        fprintf(stderr, "Function Error: 'lget()' is not supposed to get from an empty list\n");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
 }
