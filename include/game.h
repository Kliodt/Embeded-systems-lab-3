#pragma once

#include "CThreads/cthreads.h"
#include "controller.h"

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
    struct cthreads_mutex keyboardLock;

    // other necessary game-global fields
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
