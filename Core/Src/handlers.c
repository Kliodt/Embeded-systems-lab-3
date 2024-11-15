#include "handlers.h"

#include "game.h"

void buttonPressHandler(struct HandlerParameters params) {
    pressTheButton(params.direction);
}