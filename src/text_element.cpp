#include "text_element.h"

void TextElement::drawOnSprite(TFT_eSprite *sprite) {
    sprite->setTextColor(color);           // Set the text color
    sprite->drawString(text, x, y);        // Draw the text at the specified position
}

void TextElement::setText(const char *newText) {
    text = newText;
}

void TextElement::setColor(uint16_t newColor) {
    color = newColor;
}