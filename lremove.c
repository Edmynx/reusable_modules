/*
 * lremove.c -- tests lremove() function in list.c
 */

#include "list.h"
#include "make-car.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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


    /*
     * Remove from an empty list
     */
    result_car = lremove(plate_car1);
    if(result_car) {
        fprintf(stderr, "Test Error: 'lremove()' should not be able to remove an object from an empty list\n");
        exit(EXIT_FAILURE);
    }

    /*
     * Now, put some cars into the list
     */
    result_int = lput(car1);
    result_int = lput(car2);
    result_int = lput(car3);
    result_int = lput(car4);
    result_int = lput(car5);

    /*
     * Remove the last car in the list
     */
    result_car = lremove(plate_car1);
    if(!result_car) {
        fprintf(stderr, "Test Error: 'lremove()' should be able to remove the last car in the list\n");
        free(car1);
        free(car2);
        free(car3);
        free(car4);
        free(car5);
        exit(EXIT_FAILURE);
    }

    /*
     * Remove the first car in the list
     */
    result_car = lremove(plate_car5);
    if(!result_car) {
        fprintf(stderr, "Test Error: 'lremove()' should be able to remove the first car in the list\n");
        free(car1);
        free(car2);
        free(car3);
        free(car4);
        free(car5);
        exit(EXIT_FAILURE);
    }

    /*
     * Remove the middle car in the list
     */
    result_car = lremove(plate_car3);
    if(!result_car) {
        fprintf(stderr, "Test Error: 'lremove()' should be able to remove the middle car in the list\n");
        free(car1);
        free(car2);
        free(car3);
        free(car4);
        free(car5);
        exit(EXIT_FAILURE);
    }

    free(car1);
    free(car2);
    free(car3);
    free(car4);
    free(car5);
    exit(EXIT_SUCCESS);
 }
