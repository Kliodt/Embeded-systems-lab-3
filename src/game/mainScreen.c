#include "CThreads/cthreads.h"
#include "game.h"

void renderMainScreen(struct Game* game) {
    // example code
    clearScreen();
    // text test
    drawLabel(0, 0, "Main screen text");
    // draw square test
    drawSquare(0, 0, 5);
    drawSquare(5, 5, 10);
    drawSquare(15, 15, 20);
    // show changes on screen
    updateScreen();
    for (;;);
}
