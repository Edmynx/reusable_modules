#include "list.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static car_t *front = NULL;

static void print_car(car_t *cp) {
    printf("%s\n", cp->plate);
}

/* put(): place a car at the beginning of the list
 * returns 0 if successful; nonzero otherwise 
 */
int32_t lput(car_t *cp) {
    if (!cp) {
        fprintf(stderr, "Error: Value of cp is null\n");
        return 1;
    }

    cp->next = front;
    front = cp;
    return 0;
}

/* get(): remove and return the first car in the list;
 * return NULL if the list is empty
 */
car_t *lget() {
    if (!front) {
        fprintf(stderr, "Error: List is empty, returns NULL\n");
        return front;
    }

    car_t *first_element = front;
    front = front->next;

    return first_element;
}

/* apply a function to every car in the list */
void lapply(void (*fn)(car_t *cp)) {
    if (!front) {
        fprintf(stderr, "Error: Function cannot be applied to empty list\n");
    }

    car_t *current_car = front;

    while (current_car) {
        fn(current_car);
        current_car = current_car->next;
    }
}

/* remove(): find, remove, and return any car with
 * the designated plate; return NULL if not present
 */
car_t *lremove(char *platep) {
    if (!front) {
        fprintf(stderr, "Error: List is empty, returns NULL\n");
        return front;
    }

    if (strcmp(front->plate, plate) == 0) {
        lget();
    } 
    
    else {
        car_t *current_car = front->next;
        car_t *previous_car = front;

        while(current_car) {
            if (strcmp(current_car->plate, plate) == 0) {
                previous_car->next = current_car->next
                return current_car 
            }
            previous_car = current_car;
            current_car = current_car->next
        }
    }

    return NULL;
}