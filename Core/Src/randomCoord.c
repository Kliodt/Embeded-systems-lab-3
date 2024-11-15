#include "randomCoord.h"
#include <stdlib.h>
#include <time.h>

// Инициализация генератора случайных чисел с использованием системного времени
void
init_random_seed ()
{
  srand (time (NULL)); // Используем время в качестве seed
}

// Генерация случайного числа в заданном диапазоне
int
random_int (int min, int max)
{
  return min + (rand () % (max - min + 1));
}

// Генерация случайных координат на основе размеров экрана
struct Coordinate
generate_random_coord (int width, int height)
{
  struct Coordinate coord;
  coord.x = random_int (0, width - 1);
  coord.y = random_int (0, height - 1);
  return coord;
}
