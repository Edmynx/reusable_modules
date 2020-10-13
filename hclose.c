/*
 * hclose.c -- tests hclose() function in hash.c
 */

#include "hash.h"
#include "queue-objects.h"
#include "car-functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define HASHSIZE 20

int32_t main() {
    personq_t *person1, *person2, *person3, *result_person;
    carq_t *car1, *car2, *car3, *result_car;
    int32_t result_int;
    hashtable_t *htp;
    
    char name_person1[] = "Devanshi", name_person2[] = "Robert", name_person3[] = "Edmund";
    char plate_car1[] = "US-1000", plate_car2[] = "US-2000", plate_car3[] = "US-3000";
    
    double height_person1 = 6.5, height_person2 = 6.4, height_person3 = 6.1;
    double price_car1 = 36000, price_car2 = 38000, price_car3 = 40000;
    
    int age_person1 = 29, age_person2 = 20 , age_person3 = 19;
    int year_car1 = 2018, year_car2 = 2019 , year_car3 = 2020;
    
    /*
    person1 = make_car(name_person1, age_person1, height_person1);
    person2 = make_car(name_person2, age_person2, height_person2);
    person3 = make_car(name_person3, age_person3, height_person3);

    car1 = make_car(plate_car1, price_car1, year_car1);
    car2 = make_car(plate_car2, price_car2, year_car2);
    car3 = make_car(plate_car3, price_car3, year_car3);
    */

    /*
     * Close a non-existing hashtable
     */
    hclose(htp);

    /*
     * Open a new empty hashtable
     */
    htp = hopen(HASHSIZE);

    /*
     * Now, close the existing but empty hashtable
     */
    hclose(htp);
    
    /*
     * Try hashing a car into the closed hashtable
     */
    result_int = hput(htp, car1, car1->plate, sizeof(car1->plate));
    if(!result_car) {
        fprintf(stderr, "Test Error: 'hput()' should not be able to hash an object into a closed hashtable\n");
        free(car1);
        free(car2);
        free(car3);
        exit(EXIT_FAILURE);
    }

    /*
     * Open a new empty hashtable again
     */
    htp = hopen(HASHSIZE);
    
    /*
     * Hash some cars into the hashtable
     */
    hput(htp, car1, car1->plate, sizeof(car1->plate));
    hput(htp, car2, car2->plate, sizeof(car2->plate));
    hput(htp, car3, car3->plate, sizeof(car3->plate));

    /*
     * Then, close the existing and non-empty hashtable
     */
    hclose(htp);

    /*
     * Try hashing a car into the closed hashtable
     */
    result_int = hput(htp, car1, car1->plate, sizeof(car1->plate));
    if(!result_car) {
        fprintf(stderr, "Test Error: 'hput()' should not be able to hash an object into a closed hashtable\n");
        free(car1);
        free(car2);
        free(car3);
        exit(EXIT_FAILURE);
    }

    free(car1);
    free(car2);
    free(car3);
    exit(EXIT_SUCCESS);
 }
