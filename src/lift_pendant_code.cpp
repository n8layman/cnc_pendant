#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>
#include <Adafruit_NeoKey_1x4.h>
#include <seesaw_neopixel.h>
#include "Free_Fonts.h"
#include "cat_icon.h"

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

#define FREE_FONT FF4

#define SS_SWITCH       24
#define PIN_POWER_ON    15

#define Y_DIM 2 //number of rows of keys
#define X_DIM 4 //number of columns of keys

#define SEESAW_ADDR 0x36

// https://forums.adafruit.com/viewtopic.php?t=60176
// Currently this sets the neopixel colors correctly but
// not the TFT.. 
#define GREEN 0x00FF00

// Invoke library, pins defined in User_Setup.h
TFT_eSPI tft = TFT_eSPI(); 
// Sprite allows us to build each frame incrementally then push to screen just once.
TFT_eSprite background_sprite = TFT_eSprite(&tft); 
TFT_eSprite txt_sprite = TFT_eSprite(&tft); 
TFT_eSprite icon_sprite = TFT_eSprite(&tft);

int sda = 43;
int scl = 44;

// Button mode: Momentary == 1, Persistant == 0
byte buttownRow1 =  B0101;  // Buttons 3, 2, 1, 0 
byte buttownRow2 =  B0101;  // Buttons 7, 6, 5, 4 
byte buttonMode = buttownRow1 | (buttownRow2 << 4);

byte buttonState = 0;  // Initialize all elements to zero

unsigned short grays[13];

uint8_t j=0;  // this variable tracks the colors of the LEDs cycle.

bool metric = false; 

int32_t encoder_position;
int32_t encoder_color = GREEN;

Adafruit_seesaw ss;

// create a matrix of NeoKey 1x4's 
// this example is just two, one on top of another to make a 2x4 grid
Adafruit_NeoKey_1x4 nk_array[Y_DIM][X_DIM/4] = {
  { Adafruit_NeoKey_1x4(0x30) }, 
  { Adafruit_NeoKey_1x4(0x31) },
};

// pass this matrix to the multi-neokey object
Adafruit_MultiNeoKey1x4 neokey((Adafruit_NeoKey_1x4 *)nk_array, Y_DIM, X_DIM/4);

uint32_t Wheel(byte WheelPos);
NeoKey1x4Callback blink(keyEvent evt);

uint16_t Color24toRGB565(int32_t color);

void setup() {

  Serial.begin(115200);

  for(int i = 7; i>=0;i--) {
    Serial.print((char)('0' + ((buttonMode>>i)&1)));
  }

  // tft.init();
  tft.init();
  tft.setRotation(1);
  
  // background_sprite.setColorDepth(4);
  background_sprite.createSprite(320, 240);

  txt_sprite.createSprite(160, 96);
  txt_sprite.setFreeFont(FREE_FONT);
  txt_sprite.setTextColor(TFT_WHITE, TFT_BLACK);
  txt_sprite.drawString("LEAF", 0, 0);

  // icon_sprite.setColorDepth(4);
  icon_sprite.createSprite(96, 96);
  // icon_sprite.setSwapBytes(true);
  // icon_sprite.pushImage(0, 0, 31, 31, (uint16_t *)gear);

  // Start up i2c
  Wire.begin(sda, scl);

  ss.begin(0x36);
  ss.setGPIOInterrupts((uint32_t)1 << SS_SWITCH, 1); // Use for touch plate sensor
  ss.enableEncoderInterrupt();

  if (! neokey.begin()) {  // start matrix
    Serial.println("Could not start NeoKeys, check wiring?");
    while(1) delay(10);
  }

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

  // Activate all keys and set callbacks
  for(int y=0; y<Y_DIM; y++){
    for(int x=0; x<X_DIM; x++){
      neokey.registerCallback(x, y, blink);
    }
  }

  int co = 210;
  for (int i = 0; i < 13; i++) {
    grays[i] = tft.color565(co, co, co);
    co = co - 20;
  }
}

// Main loop should update display but everything to do with button
// and encoder states should be handled with interrupts
void loop() {

  encoder_position = ss.getEncoderPosition();  // Fetch the encoder position

  background_sprite.fillSprite(TFT_BLACK);

  // move to button callback so only update sprite when changung
  icon_sprite.drawBitmap(0, 0, cat_icon, 96, 96, Color24toRGB565(encoder_color), TFT_BLACK);
  neokey.read();

  // if(encoder_position>320-96) {
  //   encoder_position = 320-96;
  //   ss.setEncoderPosition(encoder_position);
  // }

  // if(encoder_position<0) {
  //   encoder_position = 0;
  //   ss.setEncoderPosition(encoder_position);
  // }

  encoder_color = Wheel((encoder_position) & 255);
  txt_sprite.pushToSprite(&background_sprite, 20, 20, TFT_BLACK); // Push sprite to screen.

  icon_sprite.pushToSprite(&background_sprite, (encoder_position % (340 + 96)) - 96, 0, TFT_BLACK);
  icon_sprite.pushToSprite(&background_sprite, ((encoder_position + 120 + 96) % (340 + 96)) - 96, 0, TFT_BLACK);
  background_sprite.pushSprite(0, 0);

  // background_sprite.fillSprite(TFT_BLACK);
  // // background_sprite.fillCircle(encoder_position, 36, 30, Color24toRGB565(encoder_color));
  // icon_sprite.pushToSprite(&background_sprite, encoder_position, 60); // Push sprite to screen.
  // background_sprite.pushSprite(0,0);

  // j++;          // make colors cycle
}

/******************************************/


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
