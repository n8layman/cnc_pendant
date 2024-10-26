#include "icon.h"

void Icon::drawOnSprite(TFT_eSprite *sprite) {
    sprite->drawBitmap(x, y, sprite, width, height, TFT_WHITE);  // Draw the icon bitmap on the sprite
}