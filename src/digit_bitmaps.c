#include <pebble.h>
#include "digit_bitmaps.h"
#include "spritesheet.h"

static const SpriteId digit_sprite_ids[4][10] = {
  {
    SPRITE_ID_DIGIT0_0,
    SPRITE_ID_DIGIT0_1,
    SPRITE_ID_DIGIT0_2,
  }, {
    SPRITE_ID_DIGIT1_0,
    SPRITE_ID_DIGIT1_1,
    SPRITE_ID_DIGIT1_2,
    SPRITE_ID_DIGIT1_3,
    SPRITE_ID_DIGIT1_4,
    SPRITE_ID_DIGIT1_5,
    SPRITE_ID_DIGIT1_6,
    SPRITE_ID_DIGIT1_7,
    SPRITE_ID_DIGIT1_8,
    SPRITE_ID_DIGIT1_9,
  }, {
    SPRITE_ID_DIGIT2_0,
    SPRITE_ID_DIGIT2_1,
    SPRITE_ID_DIGIT2_2,
    SPRITE_ID_DIGIT2_3,
    SPRITE_ID_DIGIT2_4,
    SPRITE_ID_DIGIT2_5,
  }, {
    SPRITE_ID_DIGIT3_0,
    SPRITE_ID_DIGIT3_1,
    SPRITE_ID_DIGIT3_2,
    SPRITE_ID_DIGIT3_3,
    SPRITE_ID_DIGIT3_4,
    SPRITE_ID_DIGIT3_5,
    SPRITE_ID_DIGIT3_6,
    SPRITE_ID_DIGIT3_7,
    SPRITE_ID_DIGIT3_8,
    SPRITE_ID_DIGIT3_9,
  }
};

GBitmap* get_digit_bitmap(uint8_t position, uint8_t digit) {
  return gbitmap_create_with_sprite(digit_sprite_ids[position][digit]);
}

