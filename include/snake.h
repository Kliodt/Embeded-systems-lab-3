#pragma once

#include "directions.h"
#include "snakeSegment.h"

#define MAX_SNAKE_LENGTH 100
#define INIT_SNAKE_LENGTH 10

struct Snake
{
  struct SnakeSegment body[MAX_SNAKE_LENGTH];
  int length_max;
  int length_current;
  enum Direction direction;
  const struct SnakeSegment * head;
};