// Created with TexturePacker (http://www.codeandweb.com/texturepacker)
//
// Sprite sheet: spritesheet.png (448 x 114)
//
// $TexturePacker:SmartUpdate:578ac146894a317c45885a5b00c4bf2b:41c870d11d07f924091a8f69f720def2:f255187afaed5e6299dc3d2f34bbb167$

#include <pebble.h>
#include "spritesheet.h"

static const GRect sprite_rects[] = {
  { {0, 0}, {0, 0} },
  { { 0 ,  0 }, { 27, 59 } },
  { { 27 ,  0 }, { 27, 59 } },
  { { 54 ,  0 }, { 27, 59 } },
  { { 0 ,  59 }, { 25, 55 } },
  { { 25 ,  59 }, { 25, 55 } },
  { { 50 ,  59 }, { 25, 55 } },
  { { 75 ,  59 }, { 25, 55 } },
  { { 100 ,  59 }, { 25, 55 } },
  { { 125 ,  59 }, { 25, 55 } },
  { { 150 ,  59 }, { 25, 55 } },
  { { 175 ,  59 }, { 25, 55 } },
  { { 200 ,  59 }, { 25, 55 } },
  { { 225 ,  59 }, { 25, 55 } },
  { { 250 ,  59 }, { 25, 55 } },
  { { 275 ,  59 }, { 25, 55 } },
  { { 300 ,  59 }, { 25, 55 } },
  { { 325 ,  59 }, { 25, 55 } },
  { { 350 ,  59 }, { 25, 55 } },
  { { 351 ,  0 }, { 25, 55 } },
  { { 81 ,  0 }, { 27, 59 } },
  { { 108 ,  0 }, { 27, 59 } },
  { { 135 ,  0 }, { 27, 59 } },
  { { 162 ,  0 }, { 27, 59 } },
  { { 189 ,  0 }, { 27, 59 } },
  { { 216 ,  0 }, { 27, 59 } },
  { { 243 ,  0 }, { 27, 59 } },
  { { 270 ,  0 }, { 27, 59 } },
  { { 297 ,  0 }, { 27, 59 } },
  { { 324 ,  0 }, { 27, 59 } },
  { { 386 ,  20 }, { 10, 7 } },
  { { 387 ,  42 }, { 9, 9 } },
  { { 396 ,  15 }, { 7, 7 } },
  { { 376 ,  42 }, { 11, 12 } },
  { { 387 ,  97 }, { 10, 15 } },
  { { 375 ,  71 }, { 13, 13 } },
  { { 386 ,  0 }, { 7, 20 } },
  { { 388 ,  27 }, { 10, 13 } },
  { { 376 ,  0 }, { 10, 15 } },
  { { 376 ,  15 }, { 10, 15 } },
  { { 396 ,  40 }, { 10, 13 } },
  { { 376 ,  30 }, { 12, 12 } },
  { { 375 ,  84 }, { 13, 13 } },
  { { 375 ,  55 }, { 11, 16 } },
  { { 386 ,  54 }, { 11, 12 } },
  { { 403 ,  0 }, { 3, 28 } },
  { { 393 ,  0 }, { 7, 15 } },
  { { 375 ,  97 }, { 12, 14 } },
};

static GBitmap *sprite;
GBitmap* gbitmap_create_with_sprite(SpriteId sprite_id) {
  if (!sprite) sprite = gbitmap_create_with_resource(RESOURCE_ID_SPRITE);
  return gbitmap_create_as_sub_bitmap(sprite, sprite_rects[sprite_id]);
}

void destroy_sprite() {
  gbitmap_destroy(sprite);
}