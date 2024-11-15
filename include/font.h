#pragma once

#include <stdbool.h>

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 5

extern bool FONT_ARCADE[11][CHAR_HEIGHT][CHAR_WIDTH];
extern bool FONT_GAME_OVER[8][CHAR_HEIGHT][CHAR_WIDTH];

void draw_character (int x, int y, int char_index);
void draw_text_line (const char * text, int start_x, int start_y);
void draw_character_start (int x, int y, int char_index);