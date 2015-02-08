#include <pebble.h>
#include "symmetry.h"

GBitmap* gbitmap_create_by_symmetry(GBitmap* original, uint8_t symmetry) {
  GBitmap* result = gbitmap_create_blank(original->bounds.size);

  uint16_t lines = original->bounds.size.h;
  uint16_t cols = original->bounds.size.w;
  int16_t col_orig;

  uint8_t *res_line = result->addr;
  uint8_t *orig_line = original->addr;
  bool vertical_symmetry;
  if ((vertical_symmetry = symmetry & VerticalSym)) {
    orig_line += (lines - 1) * original->row_size_bytes;
  }

  for (uint16_t l = 0; l < lines; l++) {

    for (uint16_t byte = 0; byte < original->row_size_bytes; byte++) {
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

    res_line += original->row_size_bytes;
    orig_line += (vertical_symmetry ? -1 : 1) * original->row_size_bytes;
  }

  return result;
}
