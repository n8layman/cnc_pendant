#ifndef INPUT_H
#define INPUT_H

#include <Wire.h>
#include <seesaw_neopixel.h>
#include <Adafruit_NeoKey_1x4.h>

#define SS_SWITCH       24
#define PIN_POWER_ON    15
#define SDA             43
#define SCL             44

// Set up neokey array dimensions
#define Y_DIM 2 //number of rows of keys
#define X_DIM 4 //number of columns of keys

// Global variables for button modes
extern byte buttownRow1;  // Buttons 3, 2, 1, 0 
extern byte buttownRow2;  // Buttons 7, 6, 5, 4 
extern byte buttonMode;   // Combined button mode
extern byte buttonState;  // Byte to hold button states as bits

// Callback function prototype for key presses
NeoKey1x4Callback blink(keyEvent evt);

// Other function declarations
uint32_t Wheel(byte WheelPos);
void input_init();
void input_handle();
int32_t input_get_encoder_position();

#endif // INPUT_H