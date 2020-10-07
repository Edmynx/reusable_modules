/*
 * list-test1.c -- test function for list.h
 * get() from an empty list
 */
 
#include <stdint.h>
#include "list.h"

int32_t main() {
    car_t *car1, *car2, *car3, *result_car;
    int32_t result_int;

    result = lget();
    if(result) {
        printf(stderr, "Function Error: 'lget()' is not supposed to get from an empty list\n")
        return 1
    }
    
    return 0;
 }