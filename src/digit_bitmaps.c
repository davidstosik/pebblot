#include <pebble.h>
#include "digit_bitmaps.h"
#include "spritesheet.h"

static const SpriteId digit_sprite_ids[4][10] = {
  {
    SPRITE_ID_DIGIT_0_0,
    SPRITE_ID_DIGIT_0_1,
    SPRITE_ID_DIGIT_0_2,
  }, {
    SPRITE_ID_DIGIT_1_0,
    SPRITE_ID_DIGIT_1_1,
    SPRITE_ID_DIGIT_1_2,
    SPRITE_ID_DIGIT_1_3,
    SPRITE_ID_DIGIT_1_4,
    SPRITE_ID_DIGIT_1_5,
    SPRITE_ID_DIGIT_1_6,
    SPRITE_ID_DIGIT_1_7,
    SPRITE_ID_DIGIT_1_8,
    SPRITE_ID_DIGIT_1_9,
  }, {
    SPRITE_ID_DIGIT_2_0,
    SPRITE_ID_DIGIT_2_1,
    SPRITE_ID_DIGIT_2_2,
    SPRITE_ID_DIGIT_2_3,
    SPRITE_ID_DIGIT_2_4,
    SPRITE_ID_DIGIT_2_5,
  }, {
    SPRITE_ID_DIGIT_3_0,
    SPRITE_ID_DIGIT_3_1,
    SPRITE_ID_DIGIT_3_2,
    SPRITE_ID_DIGIT_3_3,
    SPRITE_ID_DIGIT_3_4,
    SPRITE_ID_DIGIT_3_5,
    SPRITE_ID_DIGIT_3_6,
    SPRITE_ID_DIGIT_3_7,
    SPRITE_ID_DIGIT_3_8,
    SPRITE_ID_DIGIT_3_9,
  }
};

GBitmap* get_digit_bitmap(uint8_t position, uint8_t digit) {
  return gbitmap_create_with_sprite(digit_sprite_ids[position][digit]);
}

