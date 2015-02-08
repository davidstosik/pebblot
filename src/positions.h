#pragma once
#include <pebble.h>

GSize get_main_layer_size();
GSize get_big_size();
GSize get_small_size();
GRect get_digit_position(uint8_t position);
GRect get_symmetric_position(uint8_t position);

void init_positions();
