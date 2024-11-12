#include "CThreads/cthreads.h"
#include "coordinate.h"
#include "game.h"
#include <unistd.h>

void
render_main_screen (struct Game * game)
{
  // Очистка экрана и отрисовка начальных элементов
  clearScreen ();
  drawLabel (0, 0, "Main screen - Snake Game");

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

      // Перемещаем и рисуем змейку
      move_snake (&game->snake);
      clearScreen (); // Очищаем экран для перерисовки
      draw_snake (&game->snake); // Отрисовываем змейку
      updateScreen (); // Обновляем изображение на экране


      // Задержка для управления скоростью змейки
      usleep (200 * 1000);

      // game->keyboardEvent.buttonWasPressed = false; // reset the flag
      // enum Direction direction = game->keyboardEvent.direction;
      // cthreads_mutex_unlock (&game->keyboardLock);

      // // draw square test
      // drawSquare (0, 0, 5);
      // drawSquare (5, 5, 10);
      // drawSquare (15, 15, 20);
      // // show changes on screen
      // updateScreen ();
      // for (;;)
      //   ;
    }
}
