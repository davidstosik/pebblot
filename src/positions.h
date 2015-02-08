#pragma once
#include <pebble.h>

#define SteelOffsetPixels 11

GRect get_digit_position(uint8_t position, bool steel_offset);
GRect get_symmetric_position(uint8_t position, bool steel_offset);

