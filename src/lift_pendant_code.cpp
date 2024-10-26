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
Display display(&tft, 240, 320);  // Example screen dimensions

void setup() {

  // General setup
  Serial.begin(115200);

  tft.init();
  tft.setRotation(1);

  // Add elements with unique IDs
  display.addIcon("wifiIcon", 10, 10, 16, 16, wifiBitmap);    // Add WiFi icon
  display.addText("welcomeText", 50, 50, "Hello World!", TFT_WHITE);  // Add text element

  // Initial render
  display.render();
}

// Main loop should update display but everything to do with button
// and encoder states should be handled with interrupts
void loop() {

    // Update the text element with ID "welcomeText"
    display.updateText("welcomeText", "Updated Text!");

    // Refresh display contents
    display.render();

    delay(100);  // Control the refresh rate
}