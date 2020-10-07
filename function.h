#pragma once 
/*
 * function.h -- functions to be applied on cars
 *
 */

/*
 *change car plate
 */
void change_plate(car_t *cp, char *plate);

/*
 *change car price
 */
void change_price(car_t *cp, double price);

/*
 *change car year
 */
void change_year(car_t *cp, int year);

/*
 *change all attributes
 */
void change_all(car_t *cp, char *plate, double price, int year);
