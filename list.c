#include "list.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static car_t *front = NULL;

static void print_car(car_t *cp) {
    printf("%s\n", cp->plate);
}

int32_t lput(car_t *cp) {
    if (!cp) {
        fprintf(stderr, "Error: Value of cp is null\n");
        return 1;
    }

    cp->next = front;
    front = cp;
    return 0;
}

car_t *lget() {
    if (!front) {
        fprintf(stderr, "Error: Cannot get from an empty list\n");
        return front;
    }

    car_t *first_element = front;
    front = front->next;

    return first_element;
}

void lapply(void (*fn)(car_t *cp)) {
    if (!front) {
        fprintf(stderr, "Error: Function can not be applied to empty list\n");
        return;
    }

    car_t *current_car = front;

    while (current_car) {
        fn(current_car);
        current_car = current_car->next;
    }
}

car_t *lremove(char *platep) {
    if (!front) {
        fprintf(stderr, "Error: Cannot remove from an empty list\n");
        return front;
    }

    car_t *previous_car = front;
    car_t *current_car = front;
    car_t *result = NULL;

    while (current_car) {
        if (strcmp(current_car->plate, platep) == 0) {
            if (current_car == front) {
                lget();
            } else {
                result = current_car;
                previous_car->next = current_car->next;
                current_car = current_car->next;
                return result;
            }
        }

        previous_car = current_car;
        current_car = current_car->next;
    }

    return result;
}