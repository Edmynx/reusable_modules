/*
 * list-test1.c -- test function for list.h
 * put() to a non-empty list
 */

#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h>
#include "list.h"
#include "make-car.h"
#define MAXREG 10

int32_t main() {
    car_t *car1, *car2, *car3;
    int32_t result;

    char plate_car1[MAXREG] = "US-1000", plate_car2[MAXREG] = "US-2000", plate_car3[MAXREG] = "US-3000";
    double price_car1 = 36000, price_car2 = 38000, price_car3 = 40000;
    int year_car1 = 2018, year_car2 = 2019 , year_car3 = 2020;
    

    car1 = make_car(plate_car1, price_car1, year_car1);
    car2 = make_car(plate_car2, price_car2, year_car2);
    car3 = make_car(plate_car3, price_car3, year_car3);

    result = lput(car1);
    if(result) {
        fprintf(stderr, "Failed to put car1 in the empty list\n");
        free(car1);
        free(car2);
        free(car3);
        exit(EXIT_FAILURE);
    }

    result = lput(car2);
    if(result) {
        fprintf(stderr, "Failed to put car2 in the non-empty list\n");
        free(car1);
        free(car2);
        free(car3);
        exit(EXIT_FAILURE);
    }

    result = lput(car3);
    if(result) {
        fprintf(stderr, "Failed to put car3 in the non-empty list\n");
        free(car1);
        free(car2);
        free(car3);
        exit(EXIT_FAILURE);
    }

    free(car1);
    free(car2);
    free(car3);

    exit(EXIT_FAILURE);
 }
