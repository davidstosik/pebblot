#pragma once
#include <pebble.h>
#include "symmetry.h"

GBitmap* get_digit_bitmap(uint8_t position, uint8_t digit);
GBitmap* get_digit_symmetry_bitmap(uint8_t position, uint8_t digit, Symmetry symmetry);
void free_digit_bitmaps();
uint8_t hours_first_digit(struct tm * time_struct, bool hour12);
uint8_t hours_last_digit(struct tm * time_struct, bool hour12);
uint8_t minutes_first_digit(struct tm * time_struct);
uint8_t minutes_last_digit(struct tm * time_struct);
