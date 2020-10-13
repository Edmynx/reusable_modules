#pragma once 

#include <stdbool.h>

/*
 * person-functions.h -- functions that can be applied on people
 */

typedef void person_ft;	/* representation of a person is hidden */

/*
 *change person name
 */
void change_name(person_ft *pp, char *name);

/*
 *change person age
 */
void change_age(person_ft *pp, int age);

/*
 *change person height
 */
void change_height(person_ft *pp, double height);

/*
 *change all attributes
 */
void change_all(person_ft *pp, char *name, int age, double height);

/*
 *compare person name
 */
bool compare_name(person_ft *pp, char *name);

/*
 *compare person age
 */
bool compare_age(person_ft *pp, int age);

/*
 *compare person height
 */
bool compare_height(person_ft *pp, double height);

/*
 *compare all attributes
 */
bool compare_all(person_ft *pp, char *name, int age, double height);
