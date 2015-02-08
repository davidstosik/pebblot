#pragma once
#include <pebble.h>

typedef enum {
  NoSym      = 0,
  VerticalSym = 0x1,
  HorizontalSym = 0x2,
  CentralSym = VerticalSym | HorizontalSym
} Symmetry;

GBitmap*  gbitmap_create_by_symmetry(GBitmap* original, Symmetry symmetry);
