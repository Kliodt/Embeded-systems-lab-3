#include "CThreads/cthreads.h"
#include "font.h"
#include "game.h"

void draw_text_line (const char * text, int start_x, int start_y);

void
renderStartScreen (struct Game * game)
{
  clearScreen ();

  // Располагаем текст в центре экрана
  int start_x = (SCREEN_WIDTH_PX - (CHAR_WIDTH * 2 + 1) * 5) / 2;
  int start_y = (SCREEN_HEIGHT_PX - CHAR_HEIGHT * 3) / 3;

  draw_text_line ("PRESS", start_x, start_y);
  draw_text_line ("X", start_x, start_y + CHAR_HEIGHT * 2 + 2);
  draw_text_line ("TO START", start_x, start_y + (CHAR_HEIGHT * 2 + 2) * 2);
  draw_text_line ("THE GAME", start_x, start_y + (CHAR_HEIGHT * 2 + 2) * 3);

  updateScreen ();

  // Ожидание нажатия кнопки
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

  // Сброс флага нажатия и переход на главный экран
  cthreads_mutex_lock (&game->keyboardLock);
  game->keyboardEvent.buttonWasPressed = false;
  game->currentScreen = &game->mainScreen;
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
