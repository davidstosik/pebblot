#include <pebble.h>
#include "positions.h"

#include "digits.h"

static GSize main_layer_size;
static GSize big_size;
static GSize small_size;
static GRect digit_positions[4];
static GRect symmetric_positions[4];

GSize get_main_layer_size() {
  return main_layer_size;
}

GSize get_big_size() {
  return big_size;
}

GSize get_small_size() {
  return small_size;
}

GRect get_digit_position(uint8_t position) {
  return digit_positions[position];
}

GRect get_symmetric_position(uint8_t position) {
  return symmetric_positions[position];
}

void init_positions() {
  int x_to_center = 3;
  int y_to_center = 4;
  int h_space = 7;
  main_layer_size = (GSize){ .w = 144, .h = 146 };

  GPoint main_layer_center = (GPoint){
    .x = main_layer_size.w / 2,
    .y = main_layer_size.h / 2,
  };

  big_size = get_digit_bitmap(0, 0)->bounds.size;
  small_size = get_digit_bitmap(1, 0)->bounds.size;

  digit_positions[0] = (GRect){
    .origin = (GPoint){
      .x = main_layer_center.x + x_to_center,
      .y = main_layer_center.y - y_to_center - big_size.h,
    },
    .size = big_size
  };
  digit_positions[1] = (GRect){
    .origin = (GPoint){
      .x = digit_positions[0].origin.x + big_size.w + h_space,
      .y = main_layer_center.y - y_to_center - small_size.h,
    },
    .size = small_size
  };

  digit_positions[3] = (GRect){
    .origin = (GPoint){
      .x = main_layer_center.x - x_to_center - big_size.w,
      .y = main_layer_center.y + y_to_center,
    },
    .size = big_size
  };

  digit_positions[2] = (GRect){
    .origin = (GPoint){
      .x = digit_positions[3].origin.x - h_space - small_size.w,
      .y = digit_positions[3].origin.y,
    },
    .size = small_size
  };

  symmetric_positions[0] = (GRect){
    .origin = (GPoint){
      .x = digit_positions[3].origin.x,
      .y = digit_positions[0].origin.y,
    },
    .size = digit_positions[0].size,
  };

  symmetric_positions[1] = (GRect){
    .origin = (GPoint){
      .x = digit_positions[2].origin.x,
      .y = digit_positions[1].origin.y,
    },
    .size = digit_positions[1].size,
  };

  symmetric_positions[2] = (GRect){
    .origin = (GPoint){
      .x = digit_positions[1].origin.x,
      .y = digit_positions[2].origin.y,
    },
    .size = digit_positions[2].size,
  };

  symmetric_positions[3] = (GRect){
    .origin = (GPoint){
      .x = digit_positions[0].origin.x,
      .y = digit_positions[3].origin.y,
    },
    .size = digit_positions[3].size,
  };

}
