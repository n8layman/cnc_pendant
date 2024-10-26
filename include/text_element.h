#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include "drawable.h"

class TextElement : public Drawable {
public:
    TextElement(int x, int y, const char *text, uint16_t color)
        : Drawable(x, y), text(text), color(color) {}  // Call base constructor

    void drawOnSprite(TFT_eSprite *sprite) override;
    
    void setText(const char *newText);  // Update text
    void setColor(uint16_t newColor);   // Update color

private:
    const char *text;      // Text content to display
    uint16_t color;        // Color of the text
};

#endif