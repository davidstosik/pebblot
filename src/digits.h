#pragma once
#include <pebble.h>

uint32_t hours_first_digit(struct tm * time_struct);
uint32_t hours_last_digit(struct tm * time_struct);
uint32_t minutes_first_digit(struct tm * time_struct);
uint32_t minutes_last_digit(struct tm * time_struct);