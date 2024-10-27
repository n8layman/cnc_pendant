#include "Drawable.h"

// Constructor implementation, initializing sprite directly with TFT_eSPI pointer
Drawable::Drawable(TFT_eSPI *tft) : sprite(tft) {}

// Init method for post-declaration initialization
void Drawable::init(int width, int height, int x, int y, bool visible) {
    this->x = x;
    this->y = y;
    this->visible = visible;
    sprite.createSprite(width, height);  // Create the sprite with the given dimensions
}

// Overloaded function to render the sprite to a specified background sprite without transparency
void Drawable::drawTo(TFT_eSprite *background) {
    if (visible && background) {
        sprite.pushToSprite(background, x, y);  // Render sprite onto background without transparency
    }
}

// Overloaded function to render the sprite to a specified background sprite with transparency color
void Drawable::drawTo(TFT_eSprite *background, uint16_t transp) {
    if (visible && background) {
        sprite.pushToSprite(background, x, y, transp);  // Render sprite onto background with transparency
    }
}
