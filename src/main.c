#include "CThreads/cthreads.h"
#include "controller.h"
#include "game.h"
#include "handlers.h"

void* listenerThread(void* idk) {
    startListening();
    return NULL;
}

int main(void) {
    initController();

    // init button handlers
    struct HandlerInfo btnUp = {buttonPressHandler, {.direction = DIR_UP}};
    struct HandlerInfo btnDown = {buttonPressHandler, {.direction = DIR_DOWN}};
    struct HandlerInfo btnLeft = {buttonPressHandler, {.direction = DIR_LEFT}};
    struct HandlerInfo btnRight = {buttonPressHandler,
                                   {.direction = DIR_RIGHT}};
    struct HandlerInfo btnCenter = {buttonPressHandler,
                                    {.direction = DIR_CENTER}};

    setHandler(BUTTON_UP, btnUp);
    setHandler(BUTTON_DOWN, btnDown);
    setHandler(BUTTON_LEFT, btnLeft);
    setHandler(BUTTON_RIGHT, btnRight);
    setHandler(BUTTON_CENTER, btnCenter);

    // start listening in a new thread
    struct cthreads_thread thread1;
    struct cthreads_args thread1Args;
    cthreads_thread_create(&thread1, NULL, listenerThread, NULL, &thread1Args);

    // run the game in the current thread
    startGame();

    cthreads_thread_join(thread1, NULL);

    return 0;
}