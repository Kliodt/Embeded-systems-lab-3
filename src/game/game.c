#include "CThreads/cthreads.h"

#include "controller.h"
#include "coordinate.h"
#include "directions.h"
#include "game.h"
#include "snake.h"
#include "randomCoord.h"

struct Game game;

void
pressTheButton (enum Direction direction)
{
  cthreads_mutex_lock (&game.keyboardLock);
  game.keyboardEvent.buttonWasPressed = true;
  game.keyboardEvent.direction = direction;
  cthreads_mutex_unlock (&game.keyboardLock);
}

struct Game
initGame (void)
{
  // init mutex
  cthreads_mutex_init (&game.keyboardLock, NULL);
  // init screens
  game.startScreen.render = renderStartScreen;
  game.mainScreen.render = render_main_screen;
  game.endScreen.render = renderEndScreen;

  // init other fields
  game.currentScreen = &game.startScreen;

  // Инициализация змейки
  struct Coordinate init_coord = { 10, 10 }; // Начальная позиция змейки
  init_snake (&game.snake, init_coord, DIR_RIGHT);
  
  // Инициализация рандомайзера
  init_random_seed();

  return game;
}

void
startGame (void)
{
  game = initGame ();

  while (1)
    {
      game.currentScreen->render (&game);
    }
}

