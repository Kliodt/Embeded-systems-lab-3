#include "CThreads/cthreads.h"

#include "controller.h"
#include "coordinate.h"
#include "directions.h"
#include "game.h"
#include "snake.h"

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

void
init_snake (struct Snake * snake, struct Coordinate init_coord,
            enum Direction init_direction)
{
  snake->direction = init_direction;
  snake->length_current = INIT_SNAKE_LENGTH;
  snake->length_max = MAX_SNAKE_LENGTH;

  for (size_t i = INIT_SNAKE_LENGTH; i < 2; i++)
    {
      snake->body[i].coordinate.x = init_coord.x;
      snake->body[i].coordinate.y = init_coord.y;
    }

  snake->head = snake->body;
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
}
