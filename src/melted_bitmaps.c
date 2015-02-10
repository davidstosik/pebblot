#include <pebble.h>
#include "melted_bitmaps.h"

#include "digit_bitmaps.h"
#include "positions.h"

#define POSITION_MELTED_0_LEFT_TOP     {68,  21}
#define POSITION_MELTED_0_TOP_RIGHT    {92,  12}
#define POSITION_MELTED_1_TOP_LEFT     {109, 14}
#define POSITION_MELTED_1_RIGHT_TOP    {131, 30}
#define POSITION_MELTED_1_RIGHT_CENTER {134, 44}
#define POSITION_MELTED_1_RIGHT_BOTTOM {129, 67}
#define POSITION_MELTED_2_LEFT_TOP     {2,   88}
#define POSITION_MELTED_2_LEFT_CENTER  {2,  108}
#define POSITION_MELTED_2_LEFT_BOTTOM  {3,  125}
#define POSITION_MELTED_2_BOTTOM_RIGHT {25, 139}
#define POSITION_MELTED_3_BOTTOM_RIGHT {58, 141}
#define POSITION_MELTED_3_RIGHT_TOP    {65,  88}
#define POSITION_MELTED_3_RIGHT_CENTER {69, 103}
#define POSITION_MELTED_3_RIGHT_BOTTOM {65, 135}

#define SPRITE_MELTED_0_LEFT_TOP     {{361, 47}, {11, 12}}
#define SPRITE_MELTED_0_TOP_RIGHT    {{351, 44}, {10, 15}}
#define SPRITE_MELTED_1_TOP_LEFT     {{361,4}, {10, 15}}
#define SPRITE_MELTED_1_RIGHT_TOP    {{351, 3}, {10, 13}}
#define SPRITE_MELTED_1_RIGHT_CENTER {{377, 1}, {7, 20}}
#define SPRITE_MELTED_1_RIGHT_BOTTOM {{372, 46}, {13, 13}}
#define SPRITE_MELTED_2_LEFT_TOP     {{372, 33}, {13,13}}
#define SPRITE_MELTED_2_LEFT_CENTER  {{372, 21}, {12, 12}}
#define SPRITE_MELTED_2_LEFT_BOTTOM  {{351, 31}, {10, 13}}
#define SPRITE_MELTED_2_BOTTOM_RIGHT {{351, 16}, {10, 15}}
#define SPRITE_MELTED_3_BOTTOM_RIGHT {{361, 31}, {11, 16}}
#define SPRITE_MELTED_3_RIGHT_TOP    {{370, 4}, {7, 15}}
#define SPRITE_MELTED_3_RIGHT_CENTER {{385, 31}, {3, 28}}
#define SPRITE_MELTED_3_RIGHT_BOTTOM {{361, 19}, {11, 12}}

void draw_digit_external_melted_parts(uint8_t position, uint8_t digit, GContext *ctx, bool steel_offset) {
  GRect melted_sprites[2];
  GPoint positions[2];
  int count = 1;

  switch (position) {
    case 0:
      switch (digit) {
        case 1:
          melted_sprites[0] = (GRect)SPRITE_MELTED_0_TOP_RIGHT;
          positions[0] = (GPoint)POSITION_MELTED_0_TOP_RIGHT;
          break;
        case 2:
          melted_sprites[0] = (GRect)SPRITE_MELTED_0_LEFT_TOP;
          positions[0] = (GPoint)POSITION_MELTED_0_LEFT_TOP;
          break;
        default:
          count = 0;
          break;
      }
      break;
    case 1:
      switch (digit) {
        case 4:
          melted_sprites[0] = (GRect)SPRITE_MELTED_1_TOP_LEFT;
          positions[0] = (GPoint)POSITION_MELTED_1_TOP_LEFT;
          break;
        case 2:
          melted_sprites[0] = (GRect)SPRITE_MELTED_1_RIGHT_BOTTOM;
          positions[0] = (GPoint)POSITION_MELTED_1_RIGHT_BOTTOM;
          break;
        case 3:
        case 7:
          melted_sprites[0] = (GRect)SPRITE_MELTED_1_RIGHT_CENTER;
          positions[0] = (GPoint)POSITION_MELTED_1_RIGHT_CENTER;
          break;
        case 5:
        case 6:
          melted_sprites[0] = (GRect)SPRITE_MELTED_1_RIGHT_TOP;
          positions[0] = (GPoint)POSITION_MELTED_1_RIGHT_TOP;
          break;
        default:
          count = 0;
          break;
      }
      break;
    case 2:
      switch (digit) {
        case 1:
        case 4:
          melted_sprites[0] = (GRect)SPRITE_MELTED_2_BOTTOM_RIGHT;
          positions[0] = (GPoint)POSITION_MELTED_2_BOTTOM_RIGHT;
          break;
        case 2:
          melted_sprites[0] = (GRect)SPRITE_MELTED_2_LEFT_TOP;
          positions[0] = (GPoint)POSITION_MELTED_2_LEFT_TOP;
          break;
        case 3:
          melted_sprites[0] = (GRect)SPRITE_MELTED_2_LEFT_CENTER;
          positions[0] = (GPoint)POSITION_MELTED_2_LEFT_CENTER;
          break;
        case 5:
          melted_sprites[0] = (GRect)SPRITE_MELTED_2_LEFT_BOTTOM;
          positions[0] = (GPoint)POSITION_MELTED_2_LEFT_BOTTOM;
          break;
        default:
          count = 0;
          break;
      }
      break;
    case 3:
      switch (digit) {
        case 1:
        case 4:
          melted_sprites[0] = (GRect)SPRITE_MELTED_3_BOTTOM_RIGHT;
          positions[0] = (GPoint)POSITION_MELTED_3_BOTTOM_RIGHT;
          break;
        case 2:
          melted_sprites[0] = (GRect)SPRITE_MELTED_3_RIGHT_BOTTOM;
          positions[0] = (GPoint)POSITION_MELTED_3_RIGHT_BOTTOM;
          break;
        case 3:
          melted_sprites[0] = (GRect)SPRITE_MELTED_3_RIGHT_CENTER;
          positions[0] = (GPoint)POSITION_MELTED_3_RIGHT_CENTER;
          break;
        case 5:
        case 6:
          melted_sprites[0] = (GRect)SPRITE_MELTED_3_RIGHT_TOP;
          positions[0] = (GPoint)POSITION_MELTED_3_RIGHT_TOP;
          break;
        case 7:
          melted_sprites[0] = (GRect)SPRITE_MELTED_3_RIGHT_CENTER;
          positions[0] = (GPoint)POSITION_MELTED_3_RIGHT_CENTER;
          melted_sprites[1] = (GRect)SPRITE_MELTED_3_BOTTOM_RIGHT;
          positions[1] = (GPoint)POSITION_MELTED_3_BOTTOM_RIGHT;
          count = 2;
          break;
        default:
          count = 0;
          break;
      }
      break;
    default:
      count = 0;
      break;
  }

  for (int i = 0; i < count; i++) {
    GBitmap* melted_part = get_sprite((GRect)melted_sprites[i]);
    GRect rect = (GRect){ positions[i], melted_part->bounds.size };
    if (steel_offset) rect.origin.y += SteelOffsetPixels;
    graphics_draw_bitmap_in_rect(ctx, melted_part, rect);
    gbitmap_destroy(melted_part);
  }
}

