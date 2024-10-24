#include "Icon.h"

// Constructor to initialize the icon with specified bitmap, height, and width
Icon::Icon(TFT_eSPI &tft, const uint8_t *bitmap, int w, int h)
    : sprite(&tft), iconBitmap(bitmap), width(w), height(h) {
    initializeSprite();  // Initialize the sprite
}

// Initialize the sprite with the icon size
void Icon::initializeSprite() {
    sprite.createSprite(width, height);  // Create the sprite with the icon dimensions
}

// Overload () operator to return the sprite reference
TFT_eSprite& Icon::operator()() {
    return sprite;
}

// int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t fgcolor, uint16_t bgcolor
// Overloaded method to redraw a 1 bit icon
void Icon::recolor(uint16_t fgcolor, uint16_t bgcolor) {
    sprite.drawBitmap(0, 0, iconBitmap, width, height, fgcolor, bgcolor);
}

void Icon::setSwapBytes(bool swap) {
    sprite.setSwapBytes(swap);
}

// Convert 24-bit color (0xRRGGBB) to 16-bit RGB565
uint16_t Icon::Color24toRGB565(int32_t color) {
    uint8_t r = (color >> 16) & 0xFF;  // Get the Red component
    uint8_t g = (color >> 8) & 0xFF;   // Get the Green component
    uint8_t b = color & 0xFF;          // Get the Blue component

    // Convert to 16-bit RGB565 format
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}
