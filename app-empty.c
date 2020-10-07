/*
 * list-test1.c -- test function for list.h
 * apply() function to an empty list
 */

#include "list.h"
#include "function.c"
#define MAXREG 10

void func0(car_t *cp) {
    char plate[MAXREG];
    double price;
    int year;

    plate = "US-8000";
    price = 10000;
    year = 2016;

    change_all(plate, price, year);
}

int32_t main() {
    lapply(func0);
 }