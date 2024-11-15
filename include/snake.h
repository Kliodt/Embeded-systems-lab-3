#pragma once

#include "directions.h"
#include "snakeSegment.h"

#define MAX_SNAKE_LENGTH 100
#define INIT_SNAKE_LENGTH 2

struct Snake
{
  struct SnakeSegment body[MAX_SNAKE_LENGTH];
  int length_max;
  int length_current;
  enum Direction direction;
};

/**
 * Функции, описывающие поведение змейки.
 */
void init_snake (struct Snake * snake, struct Coordinate init_coord,
                 enum Direction init_direction);
int set_snake_direction (struct Snake * snake, enum Direction new_dir);
void draw_snake_segment (struct SnakeSegment * segment);
void draw_snake (struct Snake * snake);
void move_snake (struct Snake * snake);
void snake_grow (struct Snake * snake);
int is_snake_dead (struct Snake * snake);

