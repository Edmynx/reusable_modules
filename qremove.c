/*
 * qremove.c -- tests qremove() function in queue.c
 */

#include "queue.h"
#include "queue-objects.h"
#include "person-functions.h"
#include "car-functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int32_t main() {
    personq_t *person1, *person2, *person3, *result_person;
    carq_t *car1, *car2, *car3, *result_car;
    int32_t result_int;
    queue_t *qp;
    
    char name_person1[] = "Devanshi", name_person2[] = "Robert", name_person3[] = "Edmund";
    char plate_car1[] = "US-1000", plate_car2[] = "US-2000", plate_car3[] = "US-3000";
    
    double height_person1 = 6.5, height_person2 = 6.4, height_person3 = 6.1;
    double price_car1 = 36000, price_car2 = 38000, price_car3 = 40000;
    
    int age_person1 = 29, age_person2 = 20 , age_person3 = 19;
    int year_car1 = 2018, year_car2 = 2019 , year_car3 = 2020;
    
    person1 = make_car(name_person1, age_person1, height_person1);
    person2 = make_car(name_person2, age_person2, height_person2);
    person3 = make_car(name_person3, age_person3, height_person3);

    car1 = make_car(plate_car1, price_car1, year_car1);
    car2 = make_car(plate_car2, price_car2, year_car2);
    car3 = make_car(plate_car3, price_car3, year_car3);

    /*
     * Remove from a non-existing queue
     */
    result_car = qremove(qp, compare_plate, car1->plate);
    if(result_car) {
        fprintf(stderr, "Test Error: 'hremove()' is not supposed to remove an object from a non-existing hashtable\n");
        free(car1);
        free(car2);
        free(car3);
        exit(EXIT_FAILURE);
    }

    /*
     * Open a new empty queue
     */
    qp = qopen();

    /*
     * Now, remove from the existing but empty queue
     */
    result_car = qremove(qp, compare_plate, car1->plate);
    if(result_car) {
        fprintf(stderr, "Test Error: 'qremove()' is not supposed to remove an object from an empty queue\n");
        free(car1);
        free(car2);
        free(car3);
        exit(EXIT_FAILURE);
    }
    
    /*
     * Put some cars into the queue
     */
    hput(qp, car1);
    hput(qp, car2);
    hput(qp, car3);


    /*
     * Then, remove from the existing and non-empty queue
     */
    result_car = qremove(qp, compare_plate, car1->plate);
    if(!result_car) {
        fprintf(stderr, "Test Error: 'qremove()' should be able to remove car1 from queue\n");
        free(car1);
        free(car2);
        free(car3);
        exit(EXIT_FAILURE);
    }

    /*
     * Remove another object from the existing and non-empty queue
     */
    result_car = qremove(qp, compare_plate, car2->plate);
    if(!result_car) {
        fprintf(stderr, "Test Error: 'qremove()' should be able to remove car2 from queue\n");
        free(car1);
        free(car2);
        free(car3);
        exit(EXIT_FAILURE);
    }

    /*
     * Remove another object from the existing and non-empty queue
     */
    result_car = qremove(qp, compare_plate, car3->plate);
    if(!result_car) {
        fprintf(stderr, "Test Error: 'qremove()' should be able to remove car3 from queue\n");
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
