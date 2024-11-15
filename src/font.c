#include "controller.h"
#include "font.h"
#include <stdbool.h>

bool FONT_GAME_OVER[8][CHAR_HEIGHT][CHAR_WIDTH] = {
  // 'G'
  { { 1, 1, 1, 1, 0 },
    { 1, 0, 0, 0, 0 },
    { 1, 0, 1, 1, 1 },
    { 1, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 0 } },
  // 'A'
  { { 0, 1, 1, 1, 0 },
    { 1, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1 } },
  // 'M'
  { { 1, 0, 1, 0, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 1 } },
  // 'E'
  { { 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 0 },
    { 1, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1 } },
  // 'O'
  { { 0, 1, 1, 1, 0 },
    { 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1 },
    { 0, 1, 1, 1, 0 } },
  // 'V'
  { { 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1 },
    { 0, 1, 0, 1, 0 },
    { 0, 0, 1, 0, 0 } },
  // 'E' (повтор)
  { { 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 0 },
    { 1, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1 } },
  // 'R'
  { { 1, 1, 1, 1, 0 },
    { 1, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 0 },
    { 1, 0, 1, 0, 0 },
    { 1, 0, 0, 1, 0 } }
};


bool FONT_ARCADE[11][CHAR_HEIGHT][CHAR_WIDTH] = {
  // 'P'
  { { 1, 1, 1, 1, 0 },
    { 1, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 0 },
    { 1, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0 } },
  // 'R'
  { { 1, 1, 1, 1, 0 },
    { 1, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 0 },
    { 1, 0, 1, 0, 0 },
    { 1, 0, 0, 1, 0 } },
  // 'E'
  { { 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 0 },
    { 1, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1 } },
  // 'S'
  { { 0, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0 },
    { 0, 1, 1, 1, 0 },
    { 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 0 } },
  // 'X'
  { { 1, 0, 0, 0, 1 },
    { 0, 1, 0, 1, 0 },
    { 0, 0, 1, 0, 0 },
    { 0, 1, 0, 1, 0 },
    { 1, 0, 0, 0, 1 } },
  // 'T'
  { { 1, 1, 1, 1, 1 },
    { 0, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 0 } },
  // 'O'
  { { 0, 1, 1, 1, 0 },
    { 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1 },
    { 0, 1, 1, 1, 0 } },
  // 'A'
  { { 0, 1, 1, 1, 0 },
    { 1, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1 } },
  // 'H'
  { { 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1 } },
  // 'G'
  { { 0, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0 },
    { 1, 0, 0, 1, 1 },
    { 1, 0, 0, 0, 1 },
    { 0, 1, 1, 1, 0 } },
  // 'M'
  { { 1, 0, 0, 0, 1 },
    { 1, 1, 0, 1, 1 },
    { 1, 0, 1, 0, 1 },
    { 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1 } }
};

void
draw_character (int x, int y, int char_index)
{
  for (int row = 0; row < CHAR_HEIGHT; row++)
    {
      for (int col = 0; col < CHAR_WIDTH; col++)
        {
          if (FONT_GAME_OVER[char_index][row][col])
            {
              drawSquare (x + col, y + row,
                          1); // Рисуем пиксель размером 1x1
            }
        }
    }
}

void
draw_character_start (int x, int y, int char_index)
{
  for (int row = 0; row < CHAR_HEIGHT; row++)
    {
      for (int col = 0; col < CHAR_WIDTH; col++)
        {
          if (FONT_ARCADE[char_index][row][col])
            {
              drawSquare (x + col, y + row,
                          1); // Рисуем пиксель размером 1x1
            }
        }
    }
}

void
draw_text_line (const char * text, int start_x, int start_y)
{
  for (int i = 0; text[i] != '\0'; i++)
    {
      int char_index = -1;

      // Определяем индекс символа в новой таблице шрифта
      switch (text[i])
        {
        case 'P':
          char_index = 0;
          break;
        case 'R':
          char_index = 1;
          break;
        case 'E':
          char_index = 2;
          break;
        case 'S':
          char_index = 3;
          break;
        case 'X':
          char_index = 4;
          break;
        case 'T':
          char_index = 5;
          break;
        case 'O':
          char_index = 6;
          break;
        case 'A':
          char_index = 7;
          break;
        case 'H':
          char_index = 8;
          break;
        case 'G':
          char_index = 9;
          break;
        case 'M':
          char_index = 10;
          break;
        default:
          break;
        }

      if (char_index >= 0)
        {
          draw_character_start (start_x + i * (CHAR_WIDTH * 1 + 1), start_y,
                          char_index);
        }
    }
}
