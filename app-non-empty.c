/*
 * list-test1.c -- test function for list.h
 * apply() function to a non-empty list
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "list.h"
#include "make-car.h"
#include "function.h"

void func0(car_t *cp) {
    char plate[MAXREG];
    double price;
    int year;

    strcpy(plate, "US-8000");
    price = 10000;
    year = 2016;

    change_all(cp, plate, price, year);
}

int main() {
    car_t *car1, *car2, *car3;
    int32_t result;

    char plate_car1[] = "US-1000", plate_car2[] = "US-2000", plate_car3[] = "US-3000";
    double price_car1 = 36000, price_car2 = 38000, price_car3 = 40000;
    int year_car1 = 2018, year_car2 = 2019 , year_car3 = 2020;
    
    car1 = make_car(plate_car1, price_car1, year_car1);
    car2 = make_car(plate_car2, price_car2, year_car2);
    car3 = make_car(plate_car3, price_car3, year_car3);

    result = lput(car1);
    if(result) {
        fprintf(stderr, "Failed to put car1 in the empty list\n");
    }

    result = lput(car2);
    if(result) {
        fprintf(stderr, "Failed to put car2 in the non-empty list\n");
    }

    result = lput(car3);
    if(result) {
        fprintf(stderr, "Failed to put car3 in the non-empty list\n");
    }

    /*
     * apply func0
     */
    lapply(func0);

    free(car1);
    free(car2);
    free(car3);

    return 0;
 }
