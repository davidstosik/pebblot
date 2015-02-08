#include <pebble.h>
#include "digits.h"

static void init_time_struct(struct tm ** time_struct) {
  if(!*time_struct) {
    time_t now = time(NULL);
    *time_struct = localtime(&now);
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
