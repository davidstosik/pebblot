#pragma once
#include <pebble.h>
#include "symmetry.h"

GBitmap* get_digit_bitmap(uint8_t position, uint8_t digit);
GBitmap* get_sprite(GRect bounds);
void destroy_sprite();
GBitmap* get_digit_symmetry_bitmap(uint8_t position, uint8_t digit, Symmetry symmetry);
