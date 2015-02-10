#include <pebble.h>
#include "digit_bitmaps.h"

GRect digit_sprite_bounds(uint8_t position, uint8_t digit) {
  int x, y, w, h;
  switch (position) {
    case 0:
    case 3:
      w = 27;
      h = 59;
      y = 0;
      x = (position == 3) ? 0 : 10 * w;
      x += digit * w;
      break;
    case 1:
    case 2:
      w = 25;
      h = 55;
      y = 59;
      x = (position == 1) ? 0 : 10 * w;
      x += digit * w;
      break;
    default: // Should not happen
      x = y = w = h = 0;
      break;
  }
  return GRect(x, y, w, h);
}

static GBitmap *sprite;
GBitmap* get_sprite(GRect bounds) {
  if (!sprite) sprite = gbitmap_create_with_resource(RESOURCE_ID_SPRITE);
  return gbitmap_create_as_sub_bitmap(sprite, bounds);
}

GBitmap* get_digit_bitmap(uint8_t position, uint8_t digit) {
  return get_sprite(digit_sprite_bounds(position, digit));
}

void destroy_sprite() {
  gbitmap_destroy(sprite);
}

GBitmap* get_digit_symmetry_bitmap(uint8_t position, uint8_t digit, Symmetry symmetry) {
  return gbitmap_create_by_symmetry(
    get_digit_bitmap(position, digit), symmetry
  );
}

