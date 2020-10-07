/*
 * list-test1.c -- test function for list.h
 * remove() from an empty list
 */
 

#include <stdio.h>
#include <stdint.h>
#include "list.h"

int32_t main() {
    car_t *result;

    char plate_car1[] = "US-1000";

    result = lremove(plate_car1);
    if(result) {
        fprintf(stderr, "Function Error: 'lremove()' should not be able to remove from an empty list\n");
        return 1;
    }
    
    return 0;
 }
