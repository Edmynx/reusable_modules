/*
 * lapply.c -- tests lapply() function in list.c
 */

#include "list.h"
#include "make-car.h"
#include "car-functions.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

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
    car_t *car1, *car2, *car3, *result_car;
    int32_t result_int;

    char plate_car1[] = "US-1000", plate_car2[] = "US-2000", plate_car3[] = "US-3000";
    double price_car1 = 36000, price_car2 = 38000, price_car3 = 40000;
    int year_car1 = 2018, year_car2 = 2019 , year_car3 = 2020;
    
    car1 = make_car(plate_car1, price_car1, year_car1);
    car2 = make_car(plate_car2, price_car2, year_car2);
    car3 = make_car(plate_car3, price_car3, year_car3);

    /*
     * Apply function to an empty list
     */
    lapply(func0);

    /*
     * Put some cars into the list
     */
    result_int = lput(car1);
    result_int = lput(car2);
    result_int = lput(car3);

    /*
     * Now, apply function to the non-empty list
     */
    lapply(func0);

    exit(EXIT_SUCCESS);
 }
