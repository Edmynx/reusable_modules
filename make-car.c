/*
 * make-car.c -- module for making cars and linking two cars
 */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXREG 10

car_t *make_car(char* plate, double price, int year) {
    car_t *car;

    if(!(car = (car_t *)malloc(sizeof(car_t)))) {
        printf("Error: Malloc could not allocate memory for car\n");
        return NULL;
    }

    if(sizeof(plate) > MAXREG) {
        printf("Error: Car plate longer than is usual\n");
        return NULL;
    }

    car -> next = NULL;
    strcpy(car -> plate, plate);
    car -> price = price;
    car -> year = year;
    return car;
}

void link_two_cars(car_t *cp1, car_t *cp2) {
    cp1->next = cp2;
}
