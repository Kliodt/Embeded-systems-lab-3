#pragma once

#include "directions.h"
#include <stdbool.h>
#include <stdio.h>

#define BUTTONS_TOTAL 12

#define SCREEN_WIDTH_PX 100 // todo: change to real one
#define SCREEN_HEIGHT_PX 100

/**
 * Направление нажатой кнопки
 */

/**
 * Параметры функции-обработчика
 */
struct HandlerParameters
{
  enum Direction direction;
  // maybe add more parameters here
};

/**
 * Содержит информацию о функции-обработчике и параметрах,
 * с которыми она вызывается
 */
struct HandlerInfo
{
  void (*handlerFunction) (struct HandlerParameters);
  struct HandlerParameters parameters;
};

/**
 * Начальная инициализация требуемых внутренних параметров контроллера
 */
bool initController (void);

/**
 * Вывести переданную строку
 * @param x координата X
 * @param y координата Y
 * @param str NULL-terminated строка
 */
void drawLabel (int x, int y, char str[]);

/**
 * Вывести квадрат
 * @param x координата X
 * @param y координата Y
 * @param sizePx размер квадрата
 */
void drawSquare (int x, int y, int sizePx);

/**
 * Вывести на экран матрицу из пикселей
 * @param x координата X
 * @param y координата Y
 * @param matrix матрица пикселей (true - пиксель горит, false - пиксель не
 * горит)
 * @param widthPx ширина в пикселях
 * @param heightPx высота в пикселях
 */
void drawMatrix (bool ** matrix, int x, int y, int widthPx, int heightPx);

/**
 * Очистить весь экран
 */
void clearScreen (void);

/**
 * Обновить изображение на экране
 */
void updateScreen (void);

/**
 * Добавить обработчик на нажатие кнопки
 * @param buttonCode код кнопки (определены в controller.h)
 * @param handlerConfig обработчик
 */
bool setHandler (int buttonCode, struct HandlerInfo handlerConfig);

/**
 * Начать прослушивать события нажатий на кнопки
 */
void startListening (void);
