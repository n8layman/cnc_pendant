#include <Arduino.h>
#include <TFT_eSPI.h>
#include <stdint.h>
#include "Free_Fonts.h"
#include "drawable.h"
#include <seesaw_neopixel.h>
#include <Adafruit_NeoKey_1x4.h>

#include "cat_icon.h"
#include "rabbit_icon.h"
#include "turtle_icon.h"

#define FREE_FONT FF4    // Font definition for display

uint32_t Wheel(byte WheelPos);
uint16_t Color24toRGB565(int32_t color);

// Global sprites for display
TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite background(&tft);

// Icon
Drawable cat(&tft);
Drawable rabbit(&tft);
Drawable turtle(&tft);
Drawable text(&tft);

int j = 0;

void setup() {

  // General setup
  Serial.begin(115200);

  tft.init();
  tft.setRotation(1);

  background.createSprite(320, 240);

  cat.init(CAT_ICON_WIDTH, CAT_ICON_HEIGHT, 50, 30);
  cat.sprite.drawBitmap(0, 0, cat_icon, cat.sprite.width(), cat.sprite.height(), TFT_RED, TFT_BLACK);

  rabbit.init(RABBIT_ICON_WIDTH, RABBIT_ICON_HEIGHT, 0, 0);
  rabbit.sprite.drawBitmap(0, 0, rabbit_icon, rabbit.sprite.width(), rabbit.sprite.height(), TFT_GREEN, TFT_BLACK);

  turtle.init(TURTLE_ICON_WIDTH, TURTLE_ICON_HEIGHT, 0, 0);
  turtle.sprite.drawBitmap(0, 0, turtle_icon, rabbit.sprite.width(), turtle.sprite.height(), TFT_ORANGE, TFT_BLACK);

  text.init(tft.width(), tft.height(), 0, 0);
  text.sprite.setTextDatum(MC_DATUM);
  text.sprite.setTextColor(TFT_WHITE);
  text.sprite.drawString("Sprite", tft.width()/2, tft.height()/2, 4);
}

// Main loop should update display but everything to do with button
// and encoder states should be handled with interrupts
void loop() {
  j++;
  background.fillScreen(TFT_BLACK);
  cat.sprite.drawBitmap(0, 0, cat_icon, cat.sprite.width(), cat.sprite.height(),  Color24toRGB565(Wheel(j)), TFT_BLACK);
  cat.drawTo(&background);
  if((j / 100) % 2 == 1) {
    rabbit.drawTo(&background, TFT_BLACK);
  } else {
     turtle.drawTo(&background, TFT_BLACK);
  }
  text.drawTo(&background, TFT_BLACK);
  background.pushSprite(0, 0);
  delay(10); 
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return seesaw_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return seesaw_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return seesaw_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  return 0;
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