#pragma once
/* 
 * make-car.h -- public interface to car for list
 */

car_t *make_car(char* plate, double price, int year);

void link_two_cars(car_t *cp1, car_t *cp2);
