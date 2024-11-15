#include "CThreads/cthreads.h"
#include "berry.h"
#include "coordinate.h"
#include "game.h"
#include "randomCoord.h"
#include "snake.h"

#include <unistd.h>

void
render_main_screen (struct Game * game)
{
  // Очистка экрана и отрисовка начальных элементов
  clearScreen ();
  drawLabel (0, 0, "Main screen - Snake Game");

  int berry_is_placed = 0;
  struct Berry berry;

  // Цикл основного рендера экрана и управления змейкой
  while (1)
    {
      // Проверка нажатия кнопки
      cthreads_mutex_lock (&game->keyboardLock); // лок
      if (game->keyboardEvent.buttonWasPressed)
        {
          game->keyboardEvent.buttonWasPressed = false; // Сбрасываем флаг
          set_snake_direction (&game->snake, game->keyboardEvent.direction);
        }
      cthreads_mutex_unlock (&game->keyboardLock); // анлок

      if (!berry_is_placed)
        {
          place_berry (&berry, &game->snake);
          berry_is_placed = 1;
        }

      // Перемещаем и рисуем змейку
      move_snake (&game->snake);

      // съела ли змея ягодку
      if (berry_was_eaten (&berry, &game->snake))
        {
          snake_grow (&game->snake);
          berry_is_placed = 0;
        }

      clearScreen (); // Очищаем экран для перерисовки
      draw_snake (&game->snake); // Отрисовываем змейку

      if (is_snake_dead (&game->snake))
        {
          game->is_snake_dead = 1;
          game->currentScreen = &game->endScreen;
          return;
        }

      draw_berry (&berry);

      updateScreen (); // Обновляем изображение на экране

      // Задержка для управления скоростью змейки
      usleep (200 * 1000);
    }
  return;
}
