#include "input.h"
#include <Wire.h>

static Adafruit_seesaw ss;
static Adafruit_NeoKey_1x4 nk_array[2][1] = {
    { Adafruit_NeoKey_1x4(0x30) }, 
    { Adafruit_NeoKey_1x4(0x31) }
};
static Adafruit_MultiNeoKey1x4 neokey((Adafruit_NeoKey_1x4 *)nk_array, 2, 1);

int32_t encoder_color = TFT_GREEN;
int32_t encoder_position = 0;

bool metric = false; 

// Initialize global variables
byte buttownRow1 =  B0101;  // Buttons 3, 2, 1, 0 
byte buttownRow2 =  B0101;  // Buttons 7, 6, 5, 4 
byte buttonMode = buttownRow1 | (buttownRow2 << 4); // Combined button mode

void input_init() {
    
    Wire.begin(SDA, SCL);  // Start up I2C
    
    ss.begin(0x36);
    ss.setGPIOInterrupts((uint32_t)1 << SS_SWITCH, 1); // Use for touch plate sensor
    ss.enableEncoderInterrupt();

    buttonState = 0;

    // Run some colors down the keys during setup to show i2c is working
    for (uint16_t key=0; key<X_DIM*Y_DIM; key++) {
        neokey.setPixelColor(key, Wheel(map(key, 0, X_DIM*Y_DIM, 0, 255)));
        neokey.show();
        delay(50);
    }
    for (uint16_t key=0; key<X_DIM*Y_DIM; key++) {
        neokey.setPixelColor(key, 0x000000);
        neokey.show();
        delay(50);
    }
    neokey.show();

    // Activate all keys and set callbacks
    for(int y=0; y<Y_DIM; y++){
        for(int x=0; x<X_DIM; x++){
            neokey.registerCallback(x, y, blink);
        }
    }
}

void input_handle() {
    encoder_position = ss.getEncoderPosition();
    neokey.read();
}

int32_t input_get_encoder_position() {
    return encoder_position;
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

//define a callback for key presses
NeoKey1x4Callback blink(keyEvent evt) {

  uint8_t key = evt.bit.NUM;
  
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {

    if(!key) {
      metric != metric;
    }

    Serial.print("Encoder position: ");
    Serial.println(encoder_position);
    Serial.print("Key press: ");
    Serial.println(key);
 
    buttonState ^= 1 << key; // Invert bit
    neokey.setPixelColor(key, encoder_color);
    
  } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
    
    if(buttonMode & (1 << key)) {
      buttonState &= ~(1 << key); // Clear button
    }
    Serial.print("Key release: ");
    Serial.println(key);
    // neokey.setPixelColor(key, 0);
    neokey.setPixelColor(key, encoder_color);
  }

  neokey.show();
  return 0;
}

