#include "game.h"

void renderEndScreen(struct Game* game) {
    // example code
    clearScreen();
    // text test
    drawLabel(0, 0, "End screen text");
    // show changes on screen
    updateScreen();
    for (;;);
}
