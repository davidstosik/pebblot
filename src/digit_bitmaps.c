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
    0,
    RESOURCE_ID_DIGIT_2_1,
    0,
    RESOURCE_ID_DIGIT_2_3,
    RESOURCE_ID_DIGIT_2_4,
    0
  },{
    0,
    RESOURCE_ID_DIGIT_3_1,
    0,
    RESOURCE_ID_DIGIT_3_3,
    RESOURCE_ID_DIGIT_3_4,
    0,
    0,
    RESOURCE_ID_DIGIT_3_7,
    RESOURCE_ID_DIGIT_3_8,
    0,
  }
};

static GBitmap* bitmaps[4][10];
GBitmap* get_digit_bitmap(uint8_t position, uint8_t digit) {
  if (!bitmaps[position][digit]) {
    Symmetry symmetry = NoSym;
    uint8_t sym_position;
    uint8_t symmetric;
    switch (position) {
      case 2:
        switch (digit) {
          case 0:
          case 2:
          case 5:
            symmetric = digit;
            symmetry = CentralSym;
            sym_position = 1;
            break;
          case 6:
            symmetric = 9;
            symmetry = CentralSym;
            sym_position = 1;
            break;
          case 9:
            symmetric = 6;
            symmetry = CentralSym;
            sym_position = 1;
            break;
          default:
            break; /*nothing*/ }
        break;
      case 3:
        switch (digit) {
          case 0:
          case 2:
          case 5:
            symmetric = digit;
            symmetry = CentralSym;
            sym_position = 0;
            break;
          case 6:
            symmetric = 9;
            symmetry = CentralSym;
            sym_position = 0;
            break;
          case 9:
            symmetric = 6;
            symmetry = CentralSym;
            sym_position = 0;
            break;
          default:
            break; /*nothing*/ }
        break;
    }
    if (symmetry != NoSym) {
      bitmaps[position][digit] = gbitmap_create_by_symmetry(
        get_digit_bitmap(sym_position, symmetric), symmetry);
    } else {
      bitmaps[position][digit] = gbitmap_create_with_resource(DIGITS[position][digit]);
    }
  }
  return bitmaps[position][digit];
}

GBitmap* get_digit_symmetry_bitmap(uint8_t position, uint8_t digit, Symmetry symmetry) {
  return gbitmap_create_by_symmetry(
    get_digit_bitmap(position, digit), symmetry
  );
}

void free_digit_bitmaps() {
  for (int position = 0; position < 4; position++) {
    for (int digit = 0; digit < 10; digit++) {
      if (bitmaps[position][digit]) {
        gbitmap_destroy(bitmaps[position][digit]);
      }
    }
  }
}

