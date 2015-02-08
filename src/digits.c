#include <pebble.h>
#include "digits.h"
#include "symmetry.h"

static const uint8_t DIGITS[4][10] = {
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

static void init_time_struct(struct tm ** time_struct) {
  if(!*time_struct) {
    time_t now = time(NULL);
    *time_struct = localtime(&now);
  }
}


static GBitmap* bitmaps[4][4][10];
GBitmap* get_digit_bitmap(uint8_t position, uint8_t digit) {
  if (!bitmaps[NoSym][position][digit]) {
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
      bitmaps[NoSym][position][digit] = gbitmap_create_by_symmetry(
        get_digit_bitmap(sym_position, symmetric), symmetry);
    } else {
      bitmaps[NoSym][position][digit] = gbitmap_create_with_resource(DIGITS[position][digit]);
    }
  }
  return bitmaps[NoSym][position][digit];
}

GBitmap* get_digit_symmetry_bitmap(uint8_t position, uint8_t digit, Symmetry symmetry) {
  if (!bitmaps[symmetry][position][digit]) {
    bitmaps[symmetry][position][digit] = gbitmap_create_by_symmetry(
      get_digit_bitmap(position, digit), symmetry
    );
  }
  return bitmaps[symmetry][position][digit];
}

void free_digit_bitmaps() {
  for (Symmetry sym = 0; sym <= 3; sym++) {
    for (int position = 0; position < 4; position++) {
      for (int digit = 0; digit < 10; digit++) {
        if (bitmaps[sym][position][digit]) {
          gbitmap_destroy(bitmaps[sym][position][digit]);
        }
      }
    }
  }
}

uint8_t hours_first_digit(struct tm * time_struct, bool hour24) {
  init_time_struct(&time_struct);
  int hour = time_struct->tm_hour;
  if (!hour24) {
    hour = hour%12;
    hour = hour ? hour : 12;
  }
  return hour/10;
}

uint8_t hours_last_digit(struct tm * time_struct, bool hour24) {
  init_time_struct(&time_struct);
  int hour = time_struct->tm_hour;
  if (!hour24) {
    hour = hour%12;
    hour = hour ? hour : 12;
  }
  return hour%10;
}

uint8_t minutes_first_digit(struct tm * time_struct) {
  init_time_struct(&time_struct);
  return time_struct->tm_min / 10;
}

uint8_t minutes_last_digit(struct tm * time_struct) {
  init_time_struct(&time_struct);
  return time_struct->tm_min % 10;
}
