#include <string.h>

#include "controller.h"
#include "handlers.h"

struct HandlerInfo allHandlers[BUTTONS_TOTAL] = {0};

// ! ------------- this is debug things ------------------
bool screenMatrix[SCREEN_HEIGHT_PX][SCREEN_WIDTH_PX] = {0};
void printScreen(void) {
    char str[SCREEN_HEIGHT_PX * SCREEN_WIDTH_PX * 8] = {0};
    int iter = 0;
    for (int i = 0; i < SCREEN_WIDTH_PX * 2 + 2; i++) str[iter++] = '-';
    str[iter++] = '\n';
    for (int i = 0; i < SCREEN_HEIGHT_PX; i++) {
        str[iter++] = '|';
        for (int j = 0; j < SCREEN_WIDTH_PX; j++) {
            if (screenMatrix[i][j]) {
                memcpy(str + iter, "██", sizeof("██") - 1);
                iter += sizeof("██") - 1;
            } else {
                str[iter++] = ' ';
                str[iter++] = ' ';
            }
        }
        str[iter++] = '|';
        str[iter++] = '\n';
    }
    for (int i = 0; i < SCREEN_WIDTH_PX * 2 + 2; i++) str[iter++] = '-';
    str[iter++] = '\n';
    printf(str);
}
// ! -----------------------------------------------------

bool initController(void) { return true; };

void drawText(int x, int y, char str[]) {
    // todo: check screen boundaries
    // ! this is debug code
    printf("debug: text at (%d, %d): %s\n", x, y, str);
}

void drawSquare(int x, int y, int sizePx) {
    // todo: check screen boundaries
    // ! this is debug code
    for (int i = y; i < y + sizePx; i++) {
        for (int j = x; j < x + sizePx; j++) {
            screenMatrix[i][j] = true;
        }
    }
    printScreen();
};

void clearScreen(void) {
    // ! this is debug code
    for (int i = 0; i < SCREEN_HEIGHT_PX; i++) {
        for (int j = 0; j < SCREEN_WIDTH_PX; j++) {
            screenMatrix[i][j] = false;
        }
    }
    printScreen();
};

bool setHandler(int buttonCode, struct HandlerInfo handlerConfig) {
    if (buttonCode >= BUTTONS_TOTAL) return false;
    allHandlers[buttonCode] = handlerConfig;
    return true;
}

bool tryCallHandler(int buttonCode) {
    if (buttonCode >= BUTTONS_TOTAL) return false;

    struct HandlerInfo *handlerInfo = &allHandlers[buttonCode];
    if (handlerInfo->handlerFunction) {  // check if we have this handler
        handlerInfo->handlerFunction(handlerInfo->parameters);  // call handler
        return true;
    } else {
        return false;
    }
}

void startListening(void) {
    while (true) {
        break;  // listen here
    }

    // ! this is debug code
    while (1) {
        char c;
        fseek(stdin, 0, SEEK_END);
        if ((c = getchar()) == EOF) break;
        switch (c) {
            case 'a':
                tryCallHandler(BUTTON_LEFT);
                break;
            case 'w':
                tryCallHandler(BUTTON_UP);
                break;
            case 'x':
                tryCallHandler(BUTTON_DOWN);
                break;
            case 'd':
                tryCallHandler(BUTTON_RIGHT);
                break;
            case 's':
                tryCallHandler(BUTTON_CENTER);
                break;
            default:
                break;
        }
    }
}