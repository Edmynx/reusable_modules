/*
 * list-test1.c -- test function for list.h
 * put() to an empty list
 */

#include "list.h"
#include "make-car.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int32_t main() {
    car_t *car;
    int32_t result;

    char plate_car[] = "US-1000";
    double price_car = 36000;
    int year_car = 2018;

    car = make_car(plate_car, price_car, year_car);

    result = lput(car);
    if(result) {
        fprintf(stderr, "Failed to put car in the empty list\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
 }
