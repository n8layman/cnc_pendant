#include <Arduino.h>
#include <TFT_eSPI.h>
#include <stdint.h>
#include "input.h"
#include "Free_Fonts.h"

#include "icon.h"
#include "cat_icon.h"

#define FREE_FONT FF4    // Font definition for display

// Global sprites for display
TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite background_sprite = TFT_eSprite(&tft);
// TFT_eSprite cat_sprite = TFT_eSprite(&tft);
Icon cat(tft, cat_icon, 96, 96);

void setup() {

  // General setup
  Serial.begin(115200);

  // Set up display
    tft.init();
    tft.setRotation(1);

    // Initialize background sprite
    background_sprite.createSprite(320, 240);
    background_sprite.setFreeFont(FREE_FONT);
    background_sprite.setTextColor(TFT_WHITE, TFT_BLACK);

    // cat_sprite.createSprite(96,96);
    // cat_sprite.drawBitmap(0, 0, cat_icon, 96, 96, TFT_GREEN, TFT_BLACK);

    cat.recolor(TFT_GREEN);

    // Set up input
    // input_init();
}

// Main loop should update display but everything to do with button
// and encoder states should be handled with interrupts
void loop() {

    background_sprite.fillSprite(TFT_BLACK);
    // cat_sprite.pushToSprite(&background_sprite, 20, 20);
    cat().pushToSprite(&background_sprite, 20, 20);
    background_sprite.pushSprite(0, 0);

  // int32_t encoder_position = input_get_encoder_position();  // Fetch the encoder position

  // background_sprite.fillSprite(TFT_BLACK);
  // background_sprite.setTextDatum(MC_DATUM);
  // background_sprite.drawString(String(encoder_position), tft.width() / 2, tft.height() / 2);

  // // move to button callback so only update sprite when changung
  // icon_sprite.drawBitmap(0, 0, cat_icon, 96, 96, Color24toRGB565(encoder_color), TFT_BLACK);
  // neokey.read();

  // encoder_color = Wheel((encoder_position) & 255);
  // txt_sprite.pushToSprite(&background_sprite, 20, 20, TFT_BLACK); // Push sprite to screen.

  // icon_sprite.pushToSprite(&background_sprite, (encoder_position % (340 + 96)) - 96, 0, TFT_BLACK);
  // icon_sprite.pushToSprite(&background_sprite, ((encoder_position + 120 + 96) % (340 + 96)) - 96, 0, TFT_BLACK);
  // background_sprite.pushSprite(0, 0);
}