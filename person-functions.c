/*
 * person-functions.c -- functions that can be applied on cars
 */

#include "person-functions.h"
#include <string.h>
#include <stdbool.h>

#define MAXREG 10

typedef struct person_f {
	char name[MAXREG];
	int age;
	double height;
} person_ft;

/*
 *change person plate
 */
void change_name(person_ft * pp, char *name) {
    strcpy(pp->name, name);
}

/*
 *change person age
 */
void change_age(person_ft *pp, int age) {
    pp->age = age;
}

/*
 *change car year
 */
void change_height(person_ft *pp, double height) {
    pp->height = height;
}

/*
 *change all attributes
 */
void change_all(person_ft *pp, char *name, int age, double height) {
    change_plate(pp, name);
    change_price(pp, age);
    change_year(pp, height);
}

/*
 *compare car plate
 */
bool compare_name(person_ft *pp, char *name) {
    return strcmp(pp->name, name);
}

/*
 *compare car price
 */
bool compare_age(person_ft *pp, int age) {
    return pp->age == age;
}

/*
 *compare person height
 */
bool compare_height(person_ft *pp, double height) {
    return pp->height == height;
}

/*
 *compare all attributes
 */
bool compare_all(person_ft *pp, char *name, int age, double height) {
    return compare_name(pp, name) && compare_age(pp, age) && compare_height(pp, height);
}
