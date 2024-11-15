// #include <string.h>
#include <inttypes.h>
#include <stdint.h>

#include "controller.h"
#include "handlers.h"
#include "fonts.h"
#include "kb.h"
#include "oled.h"

struct HandlerInfo allHandlers[BUTTONS_TOTAL] = {0};


bool initController(void) { return true; };

// пишет текст в прямоугольник, у которого левый верхний угол находится по координатам x, y
// переносит большой текст на новую строку
// НЕ ОБНОВЛЯЕТ ЭКРАН!!!
void drawLabel(int x, int y, char str[]) {
    // todo: check screen boundaries
    // oled_Reset();
    FontDef defaultFont = Font_7x10;
    uint8_t maxSymbolsWidth = (OLED_WIDTH - x) / defaultFont.FontWidth;
    uint8_t maxSymbolsHeight = (OLED_HEIGHT - y) / defaultFont.FontHeight;
    uint8_t strLen = 0;
    while(str[strLen] != 0) {
        strLen++;
    }
    uint16_t maxSymbolsCount = maxSymbolsWidth * maxSymbolsHeight;
    if (maxSymbolsCount > 0 && strLen <= maxSymbolsCount) {
        oled_SetCursor(x, y);
        uint8_t fullSubstringCount = strLen / maxSymbolsWidth;
        uint8_t lastSubstringLen = strLen % maxSymbolsWidth;
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
        // oled_UpdateScreen();
    }
}

// рисует квадратик в координатах x, y (левый верхний угол) со стороной sizePx
// НЕ ОБНОВЛЯЕТ ЭКРАН!!!
void drawSquare(int x, int y, int sizePx) {
    // todo: check screen boundaries
    for (int i = y; i < y + sizePx; i++) {
        for (int j = x; j < x + sizePx; j++) {
            oled_DrawPixel(i, j, White);
        }
    }
}

// очистка экрана
void clearScreen(void) {
    oled_Reset();
};

void updateScreen(void) {
    oled_UpdateScreen();
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

void KB_Test(void) {
    // UART_Transmit((uint8_t *)"KB test start\n");
    uint8_t Row[4] = {ROW1, ROW2, ROW3, ROW4}, Key;
    // oled_Reset();
    // oled_WriteString("From bottom to top", Font_7x10, White);
    // OLED_KB(OLED_Keys);
    // oled_UpdateScreen();
    while (1) {
        for (int row_number = 0; row_number < 4; row_number++) {
            Key = Check_Row(Row[row_number]);
            if (Key == 0x04) {
                tryCallHandler(3 * row_number);
                // UART_Transmit ((uint8_t *)"Left pressed\n");
                // L = 1;
                // OLED_Keys[3 * i] = 0x31;
                // OLED_KB (OLED_Keys);
            } else if (Key == 0x02) {
                tryCallHandler(3 * row_number + 1);
                // UART_Transmit ((uint8_t *)"Center pressed\n");
                // C = 1;
                // OLED_Keys[1 + 3 * i] = 0x31;
                // OLED_KB (OLED_Keys);
            } else if (Key == 0x01) {
                tryCallHandler(3 * row_number + 2);
                // UART_Transmit( (uint8_t*)"Right pressed\n" );
                // R = 1;
                // OLED_Keys[2+3*i] = 0x31;
                // OLED_KB(OLED_Keys);
            }
            // UART_Transmit ((uint8_t *)"Row complete\n");
            // R = C = L = 0;
            // HAL_Delay (25);
        }
    }

    // UART_Transmit ((uint8_t *)"KB test complete\n");
}

void startListening(void) {
    KB_Test();
}
