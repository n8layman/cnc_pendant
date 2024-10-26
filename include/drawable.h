#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <TFT_eSPI.h>

class Drawable {
public:
    Drawable(int x, int y) : x(x), y(y) {}  // Constructor to set position
    virtual ~Drawable() = default;          // Virtual destructor for cleanup
    virtual void drawOnSprite(TFT_eSprite *sprite) = 0;  // Pure virtual draw function

protected:
    int x, y;  // Position of the drawable element, accessible by derived classes
};

#endif