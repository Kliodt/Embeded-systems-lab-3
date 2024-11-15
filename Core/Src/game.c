#include "game.h"

#include "controller.h"
#include "coordinate.h"
#include "directions.h"
#include "game.h"
#include "snake.h"
#include "randomCoord.h"

struct Game game;

void pressTheButton(enum Direction direction) {
    // cthreads_mutex_lock(&game.keyboardLock);
    osMutexWait(&game.keyboardLock, osWaitForever);
    game.keyboardEvent.buttonWasPressed = true;
    game.keyboardEvent.direction = direction;
    osMutexRelease(&game.keyboardLock);
    // cthreads_mutex_unlock(&game.keyboardLock);
}

struct Game initGame(void) {
    // init mutex
    const osMutexDef_t mutexDef = {.controlblock = NULL};
    // cthreads_mutex_init(&game.keyboardLock, NULL);
    game.keyboardLock = osMutexCreate(&mutexDef);
    // init screens
    game.startScreen.render = renderStartScreen;
    game.mainScreen.render = renderMainScreen;
    game.endScreen.render = renderEndScreen;

    // init other fields
    game.currentScreen = &game.startScreen;

    struct Coordinate init_coord = { 10, 10 }; // Начальная позиция змейки
    init_snake (&game.snake, init_coord, DIR_RIGHT);
    
    // Инициализация рандомайзера
    init_random_seed();

    return game;
}

void startGame(void) {
    game = initGame();

    while (1) {
        game.currentScreen->render(&game);
    }
}
