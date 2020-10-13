#pragma once 

#include <stdbool.h>

/*
 * car-functions.h -- functions that can be applied on cars
 *
 */

typedef void car_ft;	/* representation of a car is hidden */

/*
 *change car plate
 */
void change_plate(car_ft *cp, char *plate);

/*
 *change car price
 */
void change_price(car_ft *cp, double price);

/*
 *change car year
 */
void change_year(car_ft *cp, int year);

/*
 *change all attributes
 */
void change_all(car_ft *cp, char *plate, double price, int year);

/*
 *compare car plate
 */
bool compare_plate(car_ft *cp, char *plate);

/*
 *compare car price
 */
bool compare_price(car_ft *cp, double price);

/*
 *compare car year
 */
bool compare_year(car_ft *cp, int year);

/*
 *compare all attributes
 */
bool compare_all(car_ft *cp, char *plate, double price, int year);
