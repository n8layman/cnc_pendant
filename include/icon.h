#ifndef ICON_H
#define ICON_H

#include "drawable.h"

class Icon : public Drawable {
public:
    Icon(int x, int y, int width, int height, const uint16_t *bitmap)
        : Drawable(x, y), width(width), height(height), bitmap(bitmap) {}  // Call base constructor

    void drawOnSprite(TFT_eSprite *sprite) override;

private:
    int width, height;          // Width and height of the icon
    const uint16_t *bitmap;     // Pointer to bitmap data for the icon
};

#endif