/*
 * list-test1.c -- test function for list.h
 * apply() function to an empty list
 */

#include <string.h>
#include "list.h"
#include "function.h"
#define MAXREG 10

void func0(car_t *cp) {
    char plate[MAXREG];
    double price;
    int year;

    strcpy(plate, "US-8000");
    price = 10000;
    year = 2016;

    change_all(cp, plate, price, year);
}

int32_t main() {
    lapply(func0);
 }
