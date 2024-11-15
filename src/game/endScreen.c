#include "game.h"

#include "font.h"

void
renderEndScreen (struct Game * game)
{
  if (game->is_snake_dead == 1)
    {
      clearScreen ();

      // Центрируем текст по ширине
      int start_x = (SCREEN_WIDTH_PX - (CHAR_WIDTH * 1 + 3) * 8) / 2;
      // Центрируем по высоте
      int start_y = (SCREEN_HEIGHT_PX - CHAR_HEIGHT * 2) / 2;

      const char text[] = "GAMEOVER";
      for (int i = 0; i < 8; i++)
        {
          draw_character (start_x + i * (CHAR_WIDTH * 1 + 3), start_y, i);
        }

      updateScreen ();
      for (;;)
        ;
    }
}
