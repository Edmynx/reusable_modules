/*
 * list-test1.c -- test function for list.h
 * get() from a non-empty list
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "list.h"
#include "make-car.h"

int32_t main() {
    car_t *car1, *car2, *car3, *result_car;
    int32_t result_int;

    char plate_car1[] = "US-1000", plate_car2[] = "US-2000", plate_car3[] = "US-3000";
    double price_car1 = 36000, price_car2 = 38000, price_car3 = 40000;
    int year_car1 = 2018, year_car2 = 2019 , year_car3 = 2020;
    
    car1 = make_car(plate_car1, price_car1, year_car1);
    car2 = make_car(plate_car2, price_car2, year_car2);
    car3 = make_car(plate_car3, price_car3, year_car3);

    result_int = lput(car1);
    if(result_int) {
        fprintf(stderr, "Failed to put car1 in the empty list\n");
    }

    result_int = lput(car2);
    if(result_int) {
        fprintf(stderr, "Failed to put car2 in the non-empty list\n");
    }

    result_int = lput(car3);
    if(result_int) {
        fprintf(stderr, "Failed to put car3 in the non-empty list\n");
    }

    result_car = lget();
    if(!result_car) {
        fprintf(stderr, "Function Error: 'lget()' should be able to get the last car from a non-empty list\n");
        free(car1);
        free(car2);
        free(car3);
        exit(EXIT_FAILURE);
    }

    free(car1);
    free(car2);
    free(car3);
    exit(EXIT_SUCCESS);
 }
