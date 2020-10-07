/*
 * list-test1.c -- test function for list.h
 * remove() from a non-empty list
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "list.h"
#include "make-car.h"

int32_t main() {
    car_t *car1, *car2, *car3, *car4, *car5, *result_car;
    int32_t result_int;

    char plate_car1[] = "US-1000", plate_car2[] = "US-2000", plate_car3[] = "US-3000", plate_car4[] = "US-4000", plate_car5[] = "US-5000";
    double price_car1 = 36000, price_car2 = 38000, price_car3 = 40000, price_car4 = 42000, price_car5 = 44000;
    int year_car1 = 2015, year_car2 = 2016 , year_car3 = 2017, year_car4 = 2018, year_car5 = 2019;
    
    car1 = make_car(plate_car1, price_car1, year_car1);
    car2 = make_car(plate_car2, price_car2, year_car2);
    car3 = make_car(plate_car3, price_car3, year_car3);
    car4 = make_car(plate_car4, price_car4, year_car4);
    car5 = make_car(plate_car5, price_car5, year_car5);

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

    result_int = lput(car4);
    if(result_int) {
        fprintf(stderr, "Failed to put car4 in the non-empty list\n");
    }

    result_int = lput(car5);
    if(result_int) {
        fprintf(stderr, "Failed to put car5 in the non-empty list\n");
    }

    /*
     * remove the last car
     */
    result_car = lremove(plate_car1);
    if(!result_car) {
        fprintf(stderr, "Function Error: 'lremove()' should be able to remove the car associated with plate1\n");
        free(car1);
        free(car2);
        free(car3);
        free(car4);
        free(car5);
        return 1;
    }

    /*
     * remove the first car
     */
    result_car = lremove(plate_car5);
    if(!result_car) {
        fprintf(stderr, "Function Error: 'lremove()' should be able to remove the car associated with plate5\n");
        free(car1);
        free(car2);
        free(car3);
        free(car4);
        free(car5);
        return 1;
    }

    /*
     * remove the middle car
     */
    result_car = lremove(plate_car3);
    if(!result_car) {
        fprintf(stderr, "Function Error: 'lremove()' should be able to remove the car associated with plate3\n");
        free(car1);
        free(car2);
        free(car3);
        free(car4);
        free(car5);
        return 1;
    }

    free(car1);
    free(car2);
    free(car3);
    free(car4);
    free(car5);
    
    return 0;
 }
