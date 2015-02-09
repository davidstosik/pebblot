#include <pebble.h>
#include "digit_bitmaps.h"

static const uint32_t DIGITS[4][10] = {
  {
    RESOURCE_ID_DIGIT_0_0,
    RESOURCE_ID_DIGIT_0_1,
    RESOURCE_ID_DIGIT_0_2,
    0,
    0,
    RESOURCE_ID_DIGIT_0_5,
    RESOURCE_ID_DIGIT_0_6,
    0,
    0,
    RESOURCE_ID_DIGIT_0_9,
  },{
    RESOURCE_ID_DIGIT_1_0,
    RESOURCE_ID_DIGIT_1_1,
    RESOURCE_ID_DIGIT_1_2,
    RESOURCE_ID_DIGIT_1_3,
    RESOURCE_ID_DIGIT_1_4,
    RESOURCE_ID_DIGIT_1_5,
    RESOURCE_ID_DIGIT_1_6,
    RESOURCE_ID_DIGIT_1_7,
    RESOURCE_ID_DIGIT_1_8,
    RESOURCE_ID_DIGIT_1_9,
  },{
    RESOURCE_ID_DIGIT_2_0,
    RESOURCE_ID_DIGIT_2_1,
    RESOURCE_ID_DIGIT_2_2,
    RESOURCE_ID_DIGIT_2_3,
    RESOURCE_ID_DIGIT_2_4,
    RESOURCE_ID_DIGIT_2_5,
    RESOURCE_ID_DIGIT_2_6,
    0,
    0,
    RESOURCE_ID_DIGIT_2_9,
  },{
    RESOURCE_ID_DIGIT_3_0,
    RESOURCE_ID_DIGIT_3_1,
    RESOURCE_ID_DIGIT_3_2,
    RESOURCE_ID_DIGIT_3_3,
    RESOURCE_ID_DIGIT_3_4,
    RESOURCE_ID_DIGIT_3_5,
    RESOURCE_ID_DIGIT_3_6,
    RESOURCE_ID_DIGIT_3_7,
    RESOURCE_ID_DIGIT_3_8,
    RESOURCE_ID_DIGIT_3_9,
  }
};

/*static GBitmap* bitmaps[4][10];*/
GBitmap* get_digit_bitmap(uint8_t position, uint8_t digit) {
  return gbitmap_create_with_resource(DIGITS[position][digit]);
}

GBitmap* get_digit_symmetry_bitmap(uint8_t position, uint8_t digit, Symmetry symmetry) {
  return gbitmap_create_by_symmetry(
    get_digit_bitmap(position, digit), symmetry
  );
}

