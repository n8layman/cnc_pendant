#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <TFT_eSPI.h>  // Include the TFT library

struct Drawable {
    int x;                       // X position on TFT screen
    int y;                       // Y position on TFT screen
    bool visible;                // Visibility flag
    TFT_eSprite sprite;          // Sprite instance created with TFT_eSPI reference

    // Constructor with sprite dimensions, using a TFT_eSPI pointer only to initialize sprite
    Drawable(TFT_eSPI *tft);

    // Init method to initialize after default construction
    void init(int width, int height, int x, int y, bool visible = true);

    // Overloaded function to render the sprite to a specified background sprite without transparency
    void drawTo(TFT_eSprite *background);

    // Overloaded function to render the sprite to a specified background sprite with transparency color
    void drawTo(TFT_eSprite *background, uint16_t transp);
};

#endif // DRAWABLE_H
