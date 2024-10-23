#include <Arduino.h>
#include <stdint.h>
#include "display.h"
#include "input.h"

void setup() {

  Serial.begin(115200);
}

// Main loop should update display but everything to do with button
// and encoder states should be handled with interrupts
void loop() {

  int32_t encoder_position = input_get_encoder_position();  // Fetch the encoder position

  background_sprite.fillSprite(TFT_BLACK);
  background_sprite.setTextDatum(MC_DATUM);
  background_sprite.drawString(String(encoder_position), tft.width() / 2, tft.height() / 2);

  // move to button callback so only update sprite when changung
  icon_sprite.drawBitmap(0, 0, cat_icon, 96, 96, Color24toRGB565(encoder_color), TFT_BLACK);
  neokey.read();

  encoder_color = Wheel((encoder_position) & 255);
  txt_sprite.pushToSprite(&background_sprite, 20, 20, TFT_BLACK); // Push sprite to screen.

  icon_sprite.pushToSprite(&background_sprite, (encoder_position % (340 + 96)) - 96, 0, TFT_BLACK);
  icon_sprite.pushToSprite(&background_sprite, ((encoder_position + 120 + 96) % (340 + 96)) - 96, 0, TFT_BLACK);
  background_sprite.pushSprite(0, 0);
}