/*
 * function.c -- functions to be applied on cars
 */
 
#include <string.h>
#include "list.h"

/*
 *change car plate
 */
void change_plate(car_t *cp, char *plate) {
    strcpy(cp->plate, plate);
}

/*
 *change car price
 */
void change_price(car_t *cp, double price) {
    cp->price = price;
}

/*
 *change car year
 */
void change_year(car_t *cp, int year) {
    cp->year = year;
}

/*
 *change all attributes
 */
void change_all(car_t *cp, char *plate, double price, int year) {
    change_plate(cp, plate);
    change_price(cp, price);
    change_year(cp, year);
}