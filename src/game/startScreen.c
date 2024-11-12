#include "CThreads/cthreads.h"
#include "game.h"

void
renderStartScreen (struct Game * game)
{
  // example code
  clearScreen ();
  drawLabel (0, 0, "Press the button to change screen");

  // show changes on screen
  updateScreen ();

  // wait until the button will be pressed
  while (1)
    {
      cthreads_mutex_lock (&game->keyboardLock);
      if (game->keyboardEvent.buttonWasPressed)
        {
          cthreads_mutex_unlock (&game->keyboardLock);
          break;
        }
      cthreads_mutex_unlock (&game->keyboardLock);
    }
  cthreads_mutex_lock (&game->keyboardLock);
  game->keyboardEvent.buttonWasPressed = false; // reset the flag
  enum Direction direction = game->keyboardEvent.direction;
  cthreads_mutex_unlock (&game->keyboardLock);

  // set next screen according to the pressed button
  // then return so that new screen would be rendered
  switch (direction)
    {
    case DIR_UP:
    case DIR_DOWN:
      {
        game->currentScreen = &game->mainScreen;
        break;
      };
    case DIR_LEFT:
    case DIR_RIGHT:
      {
        game->currentScreen = &game->endScreen;
        break;
      };
    default:
      break;
    }
  return;
}
