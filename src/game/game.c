#include "game.h"

#include "CThreads/cthreads.h"
#include "controller.h"

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
  game.mainScreen.render = renderMainScreen;
  game.endScreen.render = renderEndScreen;

  // init other fields
  game.currentScreen = &game.startScreen;
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
