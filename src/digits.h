#pragma once
#include <pebble.h>

uint8_t get_time_digit(uint8_t position, struct tm * time_struct, bool hour24);
