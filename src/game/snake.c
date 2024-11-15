#include "controller.h"
#include "snake.h"

void
init_snake (struct Snake * snake, struct Coordinate init_coord,
            enum Direction init_direction)
{
  snake->direction = init_direction;
  snake->length_current = INIT_SNAKE_LENGTH;
  snake->length_max = MAX_SNAKE_LENGTH;

  for (int i = INIT_SNAKE_LENGTH; i < 2; i++)
    {
      snake->body[i].coordinate.x = init_coord.x;
      snake->body[i].coordinate.y = init_coord.y;
    }
}

int
set_snake_direction (struct Snake * snake, enum Direction new_dir)
{
  if ((snake->direction == DIR_UP && new_dir == DIR_DOWN)
      || (snake->direction == DIR_DOWN && new_dir == DIR_UP)
      || (snake->direction == DIR_LEFT && new_dir == DIR_RIGHT)
      || (snake->direction == DIR_RIGHT && new_dir == DIR_LEFT))
    {
      return -1;
    }
  snake->direction = new_dir;
  return 0;
}

void
draw_snake_segment (struct SnakeSegment * segment)
{
  drawSquare (segment->coordinate.x, segment->coordinate.y,
              SNAKE_SEGMENT_SIZE);
}

void
draw_snake (struct Snake * snake)
{
  for (int i = 0; i < snake->length_current; i++)
    {
      draw_snake_segment (&snake->body[i]);
    }
  updateScreen (); // Обновляем экран после отрисовки всех сегментов
}

void
move_snake (struct Snake * snake)
{
  // Перемещаем каждый сегмент тела, начиная с хвоста
  for (int i = snake->length_current - 1; i > 0; i--)
    {
      snake->body[i].coordinate.x = snake->body[i - 1].coordinate.x;
      snake->body[i].coordinate.y = snake->body[i - 1].coordinate.y;
    }

  // Обновляем координаты головы в зависимости от направления
  switch (snake->direction)
    {
    case DIR_UP:
      snake->body[0].coordinate.y -= SNAKE_SEGMENT_SIZE;
      break;
    case DIR_DOWN:
      snake->body[0].coordinate.y += SNAKE_SEGMENT_SIZE;
      break;
    case DIR_LEFT:
      snake->body[0].coordinate.x -= SNAKE_SEGMENT_SIZE;
      break;
    case DIR_RIGHT:
      snake->body[0].coordinate.x += SNAKE_SEGMENT_SIZE;
      break;
    default:
      break;
    }

  // Проверка на выход за вертикальные границы экрана и телепортация
  if (snake->body[0].coordinate.y < 0)
    {
      snake->body[0].coordinate.y = SCREEN_HEIGHT_PX - SNAKE_SEGMENT_SIZE;
    }
  else if (snake->body[0].coordinate.y >= SCREEN_HEIGHT_PX)
    {
      snake->body[0].coordinate.y = 0;
    }

  // Проверка на выход за горизонтальные границы экрана и телепортация
  if (snake->body[0].coordinate.x < 0)
    {
      snake->body[0].coordinate.x = SCREEN_WIDTH_PX - SNAKE_SEGMENT_SIZE;
    }
  else if (snake->body[0].coordinate.x >= SCREEN_WIDTH_PX)
    {
      snake->body[0].coordinate.x = 0;
    }

  // Проверка на выход за границы по вертикали и телепортация
  // if (snake->body[0].coordinate.y < 0)
  //   {
  //     snake->body[0].coordinate.y = SCREEN_HEIGHT_PX - SNAKE_SEGMENT_SIZE;
  //   }
  // else if (snake->body[0].coordinate.y >= SCREEN_HEIGHT_PX)
  //   {
  //     snake->body[0].coordinate.y = 0;
  //   }

  // if (snake->head->coordinate.x < 0)
  //   {
  //     snake->head->coordinate.x = SCREEN_WIDTH_PX - SNAKE_SEGMENT_SIZE;
  //   }
  // else if (snake->head->coordinate.x >= SCREEN_WIDTH_PX)
  //   {
  //     snake->head->coordinate.x = 0;
  //   }
}

void
snake_grow (struct Snake * snake)
{
  // Проверяем, не достигла ли змейка максимальной длины
  if (snake->length_current < snake->length_max)
    {
      // Получаем индекс последнего сегмента
      int last_index = snake->length_current - 1;

      // Копируем координаты последнего сегмента для нового сегмента
      snake->body[snake->length_current].coordinate.x
          = snake->body[last_index].coordinate.x;
      snake->body[snake->length_current].coordinate.y
          = snake->body[last_index].coordinate.y;

      // Увеличиваем текущую длину змейки
      snake->length_current++;
    }
}

int
is_snake_dead (struct Snake * snake)
{
  for (int i = 1; i < snake->length_current; i++)
    {
      if (snake->body[0].coordinate.x == snake->body[i].coordinate.x
          && snake->body[0].coordinate.y == snake->body[i].coordinate.y)
        {
          return 1;
        }
    }
    return 0;
}
