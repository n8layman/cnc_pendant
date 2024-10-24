#ifndef ICON_H
#define ICON_H

#include <TFT_eSPI.h>  // Include TFT_eSPI library for TFT functionality

class Icon {
public:
    // Public members for height and width
    int width;   // Width of the icon
    int height;  // Height of the icon

    // Constructor to initialize the icon with specified bitmap, height, and width
    Icon(TFT_eSPI &tft, const uint8_t *bitmap, int w, int h);

    // Helper to initialize the sprite
    void initializeSprite();
    
    // Overload the function call operator to return the sprite reference
    TFT_eSprite& operator()();

    // Overloaded method to draw the icon with a custom color for color icons
    void recolor(uint16_t fgcolor, uint16_t bgcolor = TFT_BLACK);

    // Private method to set byte swapping
    void setSwapBytes(bool swap);

    // Convert 24-bit color to RGB565
    uint16_t Color24toRGB565(int32_t color); 

private:

    TFT_eSprite sprite;         // The sprite used for the icon
    const uint8_t *iconBitmap; // Pointer to the bitmap data

};

#endif // ICON_H
