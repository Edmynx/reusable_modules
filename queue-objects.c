/*
 * queue-objects.c -- module for making objects that can be added to queues.
 */

#include "queue-objects.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

personq_t *make_person(char* name, int age, double height) {
    personq_t *person;

    if(!(person = (personq_t *)malloc(sizeof(personq_t)))) {
        fprintf(stderr, "Error: Malloc could not allocate memory for person\n");
        return NULL;
    }

    if(sizeof(name) > MAXNAM) {
        fprintf(stderr, "Error: Name of person cannot be longer than 50 characters\n");
        return NULL;
    }

    strcpy(person -> name, name);
    person -> age = age;
    person -> height = height;
    return person;
}

carq_t *make_car(char* plate, double price, int year) {
    carq_t *car;

    if(!(car = (carq_t *)malloc(sizeof(carq_t)))) {
        fprintf(stderr, "Error: Malloc could not allocate memory for car\n");
        return NULL;
    }

    if(sizeof(plate) > MAXREG) {
        fprintf(stderr, "Error: Car plate longer than is usual\n");
        return NULL;
    }

    strcpy(car -> plate, plate);
    car -> price = price;
    car -> year = year;
    return car;
}
