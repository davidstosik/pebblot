#include <pebble.h>
#include "digits.h"

static uint8_t hours_first_digit(struct tm * time_struct, bool hour24) {
  int hour = time_struct->tm_hour;
  if (!hour24) {
    hour = hour%12;
    hour = hour ? hour : 12;
  }
  return hour/10;
}

static uint8_t hours_last_digit(struct tm * time_struct, bool hour24) {
  int hour = time_struct->tm_hour;
  if (!hour24) {
    hour = hour%12;
    hour = hour ? hour : 12;
  }
  return hour%10;
}

static uint8_t minutes_first_digit(struct tm * time_struct) {
  return time_struct->tm_min / 10;
}

static uint8_t minutes_last_digit(struct tm * time_struct) {
  return time_struct->tm_min % 10;
}

uint8_t get_time_digit(uint8_t position, struct tm * time_struct, bool hour24) {
  switch (position) {
    case 0: return hours_first_digit(time_struct, hour24);
    case 1: return hours_last_digit(time_struct, hour24);
    case 2: return minutes_first_digit(time_struct);
    case 3: return minutes_last_digit(time_struct);
    default: return 0;
  }
}
