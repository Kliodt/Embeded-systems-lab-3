#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "controller.h"
#include "snake.h"

struct Coordinate;

struct Game;

struct GameScreen {
    void (*render)(struct Game *);
    // maybe other parameters
};

struct KeyboardEvent {
    bool buttonWasPressed;
    enum Direction direction;
};

struct Game {
    struct GameScreen startScreen;
    struct GameScreen mainScreen;
    struct GameScreen endScreen;
    struct GameScreen *currentScreen;

    struct KeyboardEvent keyboardEvent;
    // use this lock to access keyboard from multiple threads
    osMutexId keyboardLock;

    // other necessary game-global fields
    struct Snake snake;
};

/**
 * Запустить игру
 */
void startGame(void);

void renderStartScreen(struct Game *game);
void renderMainScreen(struct Game *game);
void renderEndScreen(struct Game *game);

/**
 * Послать игре сигнал о нажатии на кнопку
 * @param direction
 */
void pressTheButton(enum Direction direction);
