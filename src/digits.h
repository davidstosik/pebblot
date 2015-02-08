#pragma once
#include <pebble.h>
#include "symmetry.h"

GBitmap* get_digit_bitmap(uint8_t position, uint8_t digit);
GBitmap* get_digit_symmetry_bitmap(uint8_t position, uint8_t digit, Symmetry symmetry);
void free_digit_bitmaps();
GBitmap* hours_first_digit_bitmap(struct tm * time_struct, bool hour12);
GBitmap* hours_last_digit_bitmap(struct tm * time_struct, bool hour12);
GBitmap* minutes_first_digit_bitmap(struct tm * time_struct);
GBitmap* minutes_last_digit_bitmap(struct tm * time_struct);
