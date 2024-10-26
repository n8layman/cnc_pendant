#include "display.h"

Display::Display(TFT_eSPI *tft, int width, int height)
    : tft(tft), width(width), height(height) {
    sprite = new TFT_eSprite(tft);
    sprite->createSprite(width, height);
}

void Display::addIcon(const std::string &id, int x, int y, int width, int height, const uint16_t *bitmap) {
    Icon *icon = new Icon(x, y, width, height, bitmap);
    drawables.push_back(icon);          // Add to vector for ordered drawing
    drawableMap[id] = icon;             // Add to map for quick access by ID
}

void Display::addText(const std::string &id, int x, int y, const char *text, uint16_t color) {
    TextElement *textElement = new TextElement(x, y, text, color);
    drawables.push_back(textElement);   // Add to vector for ordered drawing
    drawableMap[id] = textElement;      // Add to map for quick access by ID
}

void Display::render() {
    sprite->fillSprite(TFT_BLACK);      // Clear the sprite

    // Draw each drawable item on the sprite in order
    for (auto* drawable : drawables) {
        drawable->drawOnSprite(sprite);
    }

    // Push the sprite to the display
    sprite->pushSprite(0, 0);           // Display the sprite
}

void Display::updateText(const std::string &id, const char *newText) {
    auto it = drawableMap.find(id);
    if (it != drawableMap.end()) {
        TextElement *textElement = dynamic_cast<TextElement*>(it->second);
        if (textElement) {
            textElement->setText(newText);  // Update the text if the element is a TextElement
        }
    }
}

void Display::cleanup() {
    for (auto* drawable : drawables) {
        delete drawable;                // Free each drawable
    }
    drawables.clear();
    drawableMap.clear();
}

Display::~Display() {
    cleanup();                          // Cleanup dynamically allocated memory
}
