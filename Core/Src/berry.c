#include "berry.h"
#include "controller.h"
#include "randomCoord.h"
#include "snake.h"

void
place_berry (struct Berry * berry, struct Snake * snake)
{
  int valid_position = 0;

  while (!valid_position)
    {
      berry->position
          = generate_random_coord (SCREEN_WIDTH_PX / SNAKE_SEGMENT_SIZE,
                                   SCREEN_HEIGHT_PX / SNAKE_SEGMENT_SIZE);
      berry->position.x *= SNAKE_SEGMENT_SIZE;
      berry->position.y *= SNAKE_SEGMENT_SIZE;

      valid_position = 1;
      for (int i = 0; i < snake->length_current; i++)
        {
          if (berry->position.x == snake->body[i].coordinate.x
              && berry->position.y == snake->body[i].coordinate.y)
            {
              valid_position = 0;
              break;
            }
        }
    }
}

void
draw_berry (struct Berry * berry)
{
  drawSquare (berry->position.x, berry->position.y, SNAKE_SEGMENT_SIZE);
}

int
berry_was_eaten (struct Berry * berry, struct Snake * snake)
{
  // Проверяем, совпадает ли положение головы змейки с положением ягодки
  return (snake->body[0].coordinate.x == berry->position.x
          && snake->body[0].coordinate.y == berry->position.y);
}
