// Created with TexturePacker (http://www.codeandweb.com/texturepacker)
//
// Sprite sheet:  ( x )
//
// $TexturePacker:SmartUpdate:7b639e82db5677c78684435b541a40c9:41c870d11d07f924091a8f69f720def2:0168b9826cd38de9376e08cf5cc43126$
#pragma once
#include <pebble.h>
#include "texture_packer.h"

enum {
  INVALID_TEXTURE_ID = -1,
  TEXTURE_ID_SPRITESHEET0,
  TEXTURE_COUNT
};

enum {
  INVALID_SPRITE_ID = -1,
  SPRITE_ID_DIGIT_0_0,
  SPRITE_ID_DIGIT_1_0,
  SPRITE_ID_DIGIT_1_1,
  SPRITE_ID_DIGIT_0_1,
  SPRITE_ID_DIGIT_1_2,
  SPRITE_ID_DIGIT_0_2,
  SPRITE_ID_DIGIT_1_3,
  SPRITE_ID_DIGIT_3_0,
  SPRITE_ID_DIGIT_1_4,
  SPRITE_ID_DIGIT_3_1,
  SPRITE_ID_DIGIT_1_5,
  SPRITE_ID_DIGIT_3_2,
  SPRITE_ID_DIGIT_1_6,
  SPRITE_ID_DIGIT_3_3,
  SPRITE_ID_DIGIT_1_7,
  SPRITE_ID_DIGIT_3_4,
  SPRITE_ID_DIGIT_1_8,
  SPRITE_ID_DIGIT_3_5,
  SPRITE_ID_DIGIT_1_9,
  SPRITE_ID_DIGIT_3_6,
  SPRITE_ID_DIGIT_2_0,
  SPRITE_ID_DIGIT_3_7,
  SPRITE_ID_DIGIT_2_1,
  SPRITE_ID_DIGIT_3_8,
  SPRITE_ID_DIGIT_2_2,
  SPRITE_ID_DIGIT_3_9,
  SPRITE_ID_DIGIT_2_3,
  SPRITE_ID_DIGIT_2_4,
  SPRITE_ID_DIGIT_2_5,
  SPRITE_ID_MELTED_EXT_3_BOTTOM_RIGHT,
  SPRITE_ID_MELTED_EXT_1_RIGHT_BOTTOM,
  SPRITE_ID_MELTED_EXT_2_LEFT_TOP,
  SPRITE_ID_MELTED_HORIZLINE_0_1_TOP,
  SPRITE_ID_MELTED_EXT_0_TOP_RIGHT,
  SPRITE_ID_MELTED_EXT_1_TOP_LEFT,
  SPRITE_ID_MELTED_EXT_2_BOTTOM_RIGHT,
  SPRITE_ID_MELTED_EXT_2_LEFT_CENTER,
  SPRITE_ID_MELTED_EXT_1_RIGHT_CENTER,
  SPRITE_ID_MELTED_CORNER_0_1_BOTTOM_LEFT,
  SPRITE_ID_MELTED_EXT_0_LEFT_TOP,
  SPRITE_ID_MELTED_EXT_3_RIGHT_BOTTOM,
  SPRITE_ID_MELTED_EXT_1_RIGHT_TOP,
  SPRITE_ID_MELTED_CORNER_GENERIC_TOP_RIGHT,
  SPRITE_ID_MELTED_EXT_2_LEFT_BOTTOM,
  SPRITE_ID_MELTED_CORNER_0_1_TOP_LEFT,
  SPRITE_ID_MELTED_EXT_3_RIGHT_TOP,
  SPRITE_ID_MELTED_EXT_3_RIGHT_CENTER,
};

static const ResourceId texture_resources[] = {
  RESOURCE_ID_SPRITESHEET0,
};

static const uint16_t sprites_per_texture[] = {
  47,
};

static const GRect sprite_rects[] = {
  { { 0 ,  0 }, { 27, 59 } },
  { { 0 ,  59 }, { 25, 55 } },
  { { 25 ,  59 }, { 25, 55 } },
  { { 27 ,  0 }, { 27, 59 } },
  { { 50 ,  59 }, { 25, 55 } },
  { { 54 ,  0 }, { 27, 59 } },
  { { 75 ,  59 }, { 25, 55 } },
  { { 81 ,  0 }, { 27, 59 } },
  { { 100 ,  59 }, { 25, 55 } },
  { { 108 ,  0 }, { 27, 59 } },
  { { 125 ,  59 }, { 25, 55 } },
  { { 135 ,  0 }, { 27, 59 } },
  { { 150 ,  59 }, { 25, 55 } },
  { { 162 ,  0 }, { 27, 59 } },
  { { 175 ,  59 }, { 25, 55 } },
  { { 189 ,  0 }, { 27, 59 } },
  { { 200 ,  59 }, { 25, 55 } },
  { { 216 ,  0 }, { 27, 59 } },
  { { 225 ,  59 }, { 25, 55 } },
  { { 243 ,  0 }, { 27, 59 } },
  { { 250 ,  59 }, { 25, 55 } },
  { { 270 ,  0 }, { 27, 59 } },
  { { 275 ,  59 }, { 25, 55 } },
  { { 297 ,  0 }, { 27, 59 } },
  { { 300 ,  59 }, { 25, 55 } },
  { { 324 ,  0 }, { 27, 59 } },
  { { 325 ,  59 }, { 25, 55 } },
  { { 350 ,  59 }, { 25, 55 } },
  { { 351 ,  0 }, { 25, 55 } },
  { { 375 ,  55 }, { 11, 16 } },
  { { 375 ,  71 }, { 13, 13 } },
  { { 375 ,  84 }, { 13, 13 } },
  { { 375 ,  97 }, { 12, 14 } },
  { { 387 ,  97 }, { 10, 15 } },
  { { 386 ,  0 }, { 10, 15 } },
  { { 376 ,  0 }, { 10, 15 } },
  { { 376 ,  15 }, { 12, 12 } },
  { { 376 ,  27 }, { 7, 20 } },
  { { 376 ,  47 }, { 10, 7 } },
  { { 383 ,  27 }, { 11, 12 } },
  { { 388 ,  15 }, { 11, 12 } },
  { { 396 ,  0 }, { 10, 13 } },
  { { 383 ,  39 }, { 7, 7 } },
  { { 386 ,  46 }, { 10, 13 } },
  { { 386 ,  59 }, { 9, 9 } },
  { { 394 ,  27 }, { 7, 15 } },
  { { 395 ,  59 }, { 3, 28 } },
};

