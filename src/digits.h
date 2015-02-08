#pragma once
#include <pebble.h>

uint8_t hours_first_digit(struct tm * time_struct, bool hour24);
uint8_t hours_last_digit(struct tm * time_struct, bool hour24);
uint8_t minutes_first_digit(struct tm * time_struct);
uint8_t minutes_last_digit(struct tm * time_struct);
