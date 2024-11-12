#pragma once

#include "CThreads/cthreads.h"
#include "controller.h"
#include "snake.h"
#include "coordinate.h"

struct Coordinate;

struct Game;

struct GameScreen
{
  void (*render) (struct Game *);
  // maybe other parameters
};

struct KeyboardEvent
{
  bool buttonWasPressed;
  enum Direction direction;
};

struct Game
{
  struct GameScreen startScreen;
  struct GameScreen mainScreen;
  struct GameScreen endScreen;
  struct GameScreen * currentScreen;

  struct KeyboardEvent keyboardEvent;
  // use this lock to access keyboard from multiple threads
  struct cthreads_mutex keyboardLock;

  // other necessary game-global fields
  struct Snake snake; 
  
};

/**
 * Запустить игру
 */
void startGame (void);

void renderStartScreen (struct Game * game);
void render_main_screen (struct Game * game);
void renderEndScreen (struct Game * game);

/**
 * Послать игре сигнал о нажатии на кнопку
 * @param direction
 */
void pressTheButton (enum Direction direction);

// Функции, описывающие поведение змейки.
void init_snake (struct Snake * snake, struct Coordinate init_coord, enum Direction init_direction);
int set_snake_direction (struct Snake * snake, enum Direction new_dir);
void draw_snake_segment (struct SnakeSegment * segment);
void draw_snake (struct Snake * snake);
void move_snake (struct Snake * snake);
