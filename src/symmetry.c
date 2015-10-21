#include <pebble.h>
#include "symmetry.h"

GBitmap* gbitmap_create_by_symmetry(GBitmap* original, uint8_t symmetry) {
  GRect bounds = gbitmap_get_bounds(original);
  GBitmap* result = gbitmap_create_blank(bounds.size, GBitmapFormat1Bit);

  uint16_t lines = bounds.size.h;
  uint16_t cols = bounds.size.w;
  int16_t col_orig;

  uint8_t *res_line = gbitmap_get_data(result);
  uint8_t *orig_line = gbitmap_get_data(original);
  bool vertical_symmetry;
  if ((vertical_symmetry = symmetry & VerticalSym)) {
    orig_line += (lines - 1) * gbitmap_get_bytes_per_row(original);
  }

  for (uint16_t l = 0; l < lines; l++) {

    for (uint16_t byte = 0; byte < gbitmap_get_bytes_per_row(original); byte++) {
      if (symmetry & HorizontalSym) {
        res_line[byte] = 0;
        for (uint8_t bit = 0; bit < 8; bit++) {
          col_orig = cols - byte*8 - bit - 1;
          if ((orig_line[col_orig/8] >> (col_orig%8)) & 1) {
            res_line[byte] += 1 << bit;
          }
        }
      } else {
        res_line[byte] = orig_line[byte];
      }
    }

    res_line += gbitmap_get_bytes_per_row(original);
    orig_line += (vertical_symmetry ? -1 : 1) * gbitmap_get_bytes_per_row(original);
  }

  return result;
}
