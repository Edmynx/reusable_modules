/*
 * car-functions.c -- functions that can be applied on cars
 */

#include "car-functions.h"
#include <string.h>
#include <stdbool.h>

#define MAXREG 10

typedef struct carstruct {
	char plate[MAXREG];
	double price;
	int year;
} carstruct_t;

/*
 *change car plate
 */
void change_plate(car_ft * cp, char *plate) {
    strcpy(((carstruct_t *) cp)->plate, plate);
}

/*
 *change car price
 */
void change_price(car_ft *cp, double price) {
    ((carstruct_t *) cp)->price = price;
}

/*
 *change car year
 */
void change_year(car_ft *cp, int year) {
    ((carstruct_t *) cp)->year = year;
}

/*
 *change all attributes
 */
void change_all(car_ft *cp, char *plate, double price, int year) {
    change_plate(cp, plate);
    change_price(cp, price);
    change_year(cp, year);
}

/*
 *compare car plate
 */
bool compare_plate(car_ft *cp, char *plate) {
    return strcmp(((carstruct_t *) cp)->plate, plate);
}

/*
 *compare car price
 */
bool compare_price(car_ft *cp, double price) {
    return ((carstruct_t *) cp)->price == price;
}

/*
 *compare car year
 */
bool compare_year(car_ft *cp, int year) {
    return ((carstruct_t *) cp)->year == year;
}

/*
 *compare all attributes
 */
bool compare_all(car_ft *cp, char *plate, double price, int year) {
    return compare_plate(cp, plate) && compare_price(cp, price) && compare_year(cp, year);
}
