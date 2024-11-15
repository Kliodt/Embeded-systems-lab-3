#pragma once

#include "coordinate.h"

/**
 * Инициализация генератора случайных чисел
 */
void init_random_seed (); 

/**
 * Генерация случайного числа в определённом диапазоне
 */
int random_int (int min, int max); 

/**
 * Генерация случайных координат
 */
struct Coordinate
generate_random_coord (int width, int height); 