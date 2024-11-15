#pragma once

#include "coordinate.h"
#include "snake.h"
#include "stdbool.h"

struct Snake;

struct Berry
{
  struct Coordinate position;
};

/**
 * Логика ягодок.
 */
void place_berry (struct Berry * berry, struct Snake * snake);
void draw_berry (struct Berry * berry);
int berry_was_eaten (struct Berry * berry, struct Snake * snake);