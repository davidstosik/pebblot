#include <pebble.h>
#include "symmetry.h"
#include "positions.h"

void pebblot_symmetry(GBitmap* buffer, bool steel_offset) {

  GPoint center = grect_center_point(&(buffer->bounds));
  if (steel_offset) center.y += SteelOffsetPixels;

  uint8_t lines = buffer->bounds.size.h;
  uint8_t cols = buffer->bounds.size.w;
  uint8_t col_orig;

  uint8_t *line = buffer->addr;

  uint16_t useful_bytes = cols / 8 + (cols % 8 ? 1 : 0);
  uint16_t last_byte_pos = (useful_bytes - 1) / 2;

  uint8_t write_byte, mask;
  uint8_t min_byte, max_byte, bit_min, bit_max;

  for (uint16_t l = 0; l < lines; l++) {
    if (l < center.y) {
      min_byte = 0;
      max_byte = last_byte_pos;
    } else {
      min_byte = last_byte_pos + (cols % 8 ? 0 : 1);
      max_byte = useful_bytes - 1;
    }
    for (uint16_t byte_pos = min_byte; byte_pos <= max_byte; byte_pos++) {
      write_byte = 0;
      mask = 0;
      bit_min = 0;
      bit_max = 7;
      if (byte_pos == last_byte_pos) {
        if (byte_pos == min_byte) {
          bit_min = (center.x - 1) % 8 + 1;
        } else {
          bit_max = (center.x - 1) % 8;
        }
      } else if (byte_pos == max_byte) {
        bit_max = (cols - 1) % 8;
      }
      for (uint8_t bit = bit_min; bit <= bit_max; bit++) {
        col_orig = cols - byte_pos*8 - bit - 1;
        if ((line[col_orig/8] >> (col_orig%8)) & 1) {
          write_byte += 1 << bit;
        }
        mask += 1 << bit;
      }
      line[byte_pos] = (write_byte & mask) + (line[byte_pos] & ~mask);
    }
    line += buffer->row_size_bytes;
  }
}
