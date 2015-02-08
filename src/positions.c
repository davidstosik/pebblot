#include <pebble.h>
#include "positions.h"

#include "digits.h"

#define DigitBigSize {27, 59}
#define DigitSmallSize {25, 55}
#define X1 10
#define X2 42
#define X3 75
#define X4 109
#define Y1 21
#define Y2 25
#define Y3 88


static const GRect digit_positions[4] = {
  { { X3, Y1 }, DigitBigSize },
  { { X4, Y2 }, DigitSmallSize },
  { { X1, Y3 }, DigitSmallSize },
  { { X2, Y3 }, DigitBigSize },
};

static const GRect symmetric_positions[4] = {
  { { X2, Y1 }, DigitBigSize },
  { { X1, Y2 }, DigitSmallSize },
  { { X4, Y3 }, DigitSmallSize },
  { { X3, Y3 }, DigitBigSize },
};

GRect get_digit_position(uint8_t position) {
  GRect result = digit_positions[position];
  return result;
}

GRect get_symmetric_position(uint8_t position) {
  GRect result = symmetric_positions[position];
  return result;
}

