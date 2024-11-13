#include <string.h>

#include "controller.h"
#include "handlers.h"
#include "fonts.h"
#include "oled.h"

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

// пишет текст в прямоугольник, у которого левый верхний угол находится по координатам x, y
// переносит большой текст на новую строку
// ОБНОВЛЯЕТ ЭКРАН!!!
void drawLabel(int x, int y, char str[]) {
    // todo: check screen boundaries
    oled_Reset();
    FontDef defaultFont = Font_7x10;
    u_int8_t maxSymbolsWidth = (OLED_WIDTH - x) / defaultFont.FontWidth;
    u_int8_t maxSymbolsHeight = (OLED_HEIGHT - y) / defaultFont.FontHeight;
    u_int8_t strLen = 0;
    while(str[strLen] != 0) {
        strLen++;
    }
    u_int16_t maxSymbolsCount = maxSymbolsWidth * maxSymbolsHeight;
    if (maxSymbolsCount > 0 && strLen <= maxSymbolsCount) {
        oled_SetCursor(x, y);
        u_int8_t fullSubstringCount = strLen / maxSymbolsWidth;
        u_int8_t lastSubstringLen = strLen % maxSymbolsWidth;
        for (int i = 0; i < fullSubstringCount; i++) {
            oled_SetCursor(x, y + i * 2 * maxSymbolsHeight);
            char substring[maxSymbolsWidth + 1];
            for (int j = 0; j < maxSymbolsWidth; j++) {
                substring[j] = str[j + i * maxSymbolsWidth];
            }
            substring[maxSymbolsWidth] = '\0';
            oled_WriteString(substring, defaultFont, White);
        }
        oled_SetCursor(x, y + fullSubstringCount * maxSymbolsHeight * 2);
        char lastSubstring[lastSubstringLen + 1];
        for (int j = 0; j < lastSubstringLen; j++) {
            lastSubstring[j] = str[j + fullSubstringCount * maxSymbolsWidth];
        }
        lastSubstring[lastSubstringLen] = '\0';
        oled_WriteString(lastSubstring, defaultFont, White);
        oled_UpdateScreen();
    }
}

// рисует квадратик в координатах x, y (левый верхний угол) со стороной sizePx
// НЕ ОБНОВЛЯЕТ ЭКРАН!!!
void drawSquare(int x, int y, int sizePx) {
    // todo: check screen boundaries
    // ! this is debug code
    for (int i = y; i < y + sizePx; i++) {
        for (int j = x; j < x + sizePx; j++) {
            oled_DrawPixel(i, j, White);
        }
    }
}

// не реализовано
void drawMatrix(bool** matrix, int x, int y, int widthPx, int heightPx) {
    // ! WARNING: didn't test it, but should work
    // todo: check screen boundaries
    // ! this is debug code
    for (int i = y; i < y + heightPx; i++) {
        for (int j = x; j < x + widthPx; j++) {
            screenMatrix[i][j] = matrix[i][j];
        }
    }
}

// очистка экрана
void clearScreen(void) {
    oled_Reset();
};

void updateScreen(void) {
    printScreen();
}

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