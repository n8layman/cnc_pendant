#include "display.h"

// Global sprites for display
TFT_eSPI tft = TFT_eSPI(); 

static TFT_eSprite background_sprite = TFT_eSprite(&tft);
static TFT_eSprite txt_sprite = TFT_eSprite(&tft);
static TFT_eSprite icon_sprite = TFT_eSprite(&tft);

void display_init(TFT_eSPI *tft) {
    tft->init();
    tft->setRotation(1);

    // Initialize background sprite
    background_sprite.createSprite(320, 240);
    background_sprite.setFreeFont(FREE_FONT);
    background_sprite.setTextColor(TFT_WHITE, TFT_BLACK);

    // Initialize icon sprite
    icon_sprite.createSprite(96, 96);
}

void display_update(int32_t encoder_position, int32_t encoder_color) {
    background_sprite.fillSprite(TFT_BLACK);
    display_show_text(encoder_position);
    display_show_icon(encoder_position, encoder_color);
    background_sprite.pushSprite(0, 0);
}

void display_show_text(int32_t encoder_position) {
    background_sprite.setTextDatum(MC_DATUM);
    background_sprite.drawString(String(encoder_position), 160, 120);  // Center of the screen
}

void display_show_icon(int32_t encoder_position, int32_t encoder_color) {
    icon_sprite.drawBitmap(0, 0, cat_icon, 96, 96, encoder_color, TFT_BLACK);
    // Push icon sprite to different positions
    icon_sprite.pushToSprite(&background_sprite, (encoder_position % (320 + 96)) - 96, 0, TFT_BLACK);
}

// Function to convert 24-bit int32_t (0xRRGGBB) to 16-bit RGB565
uint16_t Color24toRGB565(int32_t color) {
  // Extract red, green, and blue components from the 24-bit color
  uint8_t r = (color >> 16) & 0xFF; // Get the Red component (upper 8 bits)
  uint8_t g = (color >> 8) & 0xFF;  // Get the Green component (middle 8 bits)
  uint8_t b = color & 0xFF;         // Get the Blue component (lower 8 bits)

  // Convert to 16-bit RGB565
  uint16_t rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
  
  return rgb565;
}