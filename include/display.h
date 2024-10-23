#ifndef DISPLAY_H
#define DISPLAY_H

// General display
#include <TFT_eSPI.h>
#include <SPI.h>
#include "Free_Fonts.h"

// Icons
#include "cat_icon.h"

#define FREE_FONT FF4    // Font definition for display

uint16_t Color24toRGB565(int32_t color);

void display_update(int32_t encoder_position, int32_t encoder_color);
void display_show_icon(int32_t encoder_position, int32_t encoder_color);
void display_show_text(int32_t encoder_position);
void display_init(TFT_eSPI *tft);
#endif // DISPLAY_H