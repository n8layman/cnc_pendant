#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>
#include <vector>
#include <unordered_map>
#include <string>
#include "drawable.h"
#include "icon.h"
#include "text_element.h"

class Display {
public:
    Display(TFT_eSPI *tft, int width, int height);

    // Methods to add drawable types with identifiers
    void addIcon(const std::string &id, int x, int y, int width, int height, const uint16_t *bitmap);
    void addText(const std::string &id, int x, int y, const char *text, uint16_t color);
    void render();
    void updateText(const std::string &id, const char *newText);  // Update text of a specific TextElement

    ~Display();

private:
    TFT_eSPI *tft;
    TFT_eSprite *sprite;
    int width, height;

    // Both containers store pointers to Drawable objects
    std::unordered_map<std::string, Drawable*> drawableMap;  // Map for quick access by ID
    std::vector<Drawable*> drawables;                        // Vector for render order

    void cleanup();  // Internal cleanup function
};

#endif
