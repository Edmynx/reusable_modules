#include "list.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static car_t *front = NULL;

int32_t lput(car_t *cp) {
    if (!cp) {
        fprintf(stderr, "Error: Value of *cp is null\n");
        return 1;
    }

    if (front == NULL) {
        front = cp;
        return 0;
    }

    car_t *first_car = front;

    if (first_car->next == NULL) {
        cp->next = first_car;
        front = cp;
        return 0;
    }

    car_t *car_to_add = cp;

    if (car_to_add->next == NULL) {
        car_to_add->next = first_car;
        front = car_to_add;
    }

    return 0;
}

car_t *lget() {
    if (front == NULL) {
        fprintf(stderr, "Error: List is empty\n");
        return NULL;
    }

    car_t *first_car = front;
    front = front->next;

    return first_car;
}

void lapply(void (*fn)(car_t *cp)) {
    if (front == NULL) {
        fprintf(stderr, "Error: List is empty\n");
    }
    
    car_t *ptr = front;

    while (ptr != NULL) {
        fn(ptr);
        ptr = ptr->next;
    }
}

car_t *lremove(char *platep) {
    if (front == NULL) {
        fprintf(stderr, "Error: List is empty\n");
        return NULL;
    }

    if (front->next == NULL) {
        if (strcmp(front->plate, platep) == 0) {
            return front;
        } else {
            fprintf(stderr, "Error: No such car exists\n");
            return NULL;
        }
    }

    if (strcmp(front->plate, platep) == 0) {
        return front;
    }

    car_t *current_car = front;
    car_t *next_car = front->next;

    while (next_car != NULL) {
        if (strcmp(next_car->plate, platep) == 0) {
            car_t *temp_ptr = next_car;
            current_car->next = next_car->next;
            return temp_ptr;
        }

        next_car = next_car->next;
        current_car = current_car->next;
    }

    return NULL;
}

int main(void) {
    car_t car;
    car.next = NULL;
    strcpy(car.plate, "work");
    car.price = 5.00;
    car.year = 2000;

    car_t anothercar;
    anothercar.next = NULL;
    strcpy(anothercar.plate, "pls");
    anothercar.price = 1.00;
    anothercar.year = 1900;

    car_t carro;
    carro.next = NULL;
    strcpy(carro.plate, "hola");
    carro.price = 10.00;
    carro.year = 1950;
    
    lput(NULL);
    lput(&car);
    lput(&carro);

    car_t *temp = front;
    printf("%d\n", temp->year);

    temp = temp->next;
    printf("%d\n", temp->year);

    car_t *c = lget();
    printf("%d\n", c->year);

    lput(&anothercar);

    c = lget();
    printf("%d\n", c->year);

    c = lget();
    printf("%d\n", c->year);

    lremove(NULL);

    lput(&car);
    lput(&anothercar);
    lput(&carro);

    car_t *removed = lremove("pls");
    printf("%s", removed->plate);

    // removed = lremove("hola");
    // printf("%s", removed->plate);
}