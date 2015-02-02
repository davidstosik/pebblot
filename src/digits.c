#include <pebble.h>
#include "digits.h"

static const int HOURS_FIRST_DIGITS[3] = {
  RESOURCE_ID_HOURS_FIRST_0,
  RESOURCE_ID_HOURS_FIRST_1,
  RESOURCE_ID_HOURS_FIRST_2,
};

static const int HOURS_LAST_DIGITS[10] = {
  RESOURCE_ID_HOURS_LAST_0,
  RESOURCE_ID_HOURS_LAST_1,
  RESOURCE_ID_HOURS_LAST_2,
  RESOURCE_ID_HOURS_LAST_3,
  RESOURCE_ID_HOURS_LAST_4,
  RESOURCE_ID_HOURS_LAST_5,
  RESOURCE_ID_HOURS_LAST_6,
  RESOURCE_ID_HOURS_LAST_7,
  RESOURCE_ID_HOURS_LAST_8,
  RESOURCE_ID_HOURS_LAST_9,
};

static const int MINUTES_FIRST_DIGITS[6] = {
  RESOURCE_ID_MINUTES_FIRST_0,
  RESOURCE_ID_MINUTES_FIRST_1,
  RESOURCE_ID_MINUTES_FIRST_2,
  RESOURCE_ID_MINUTES_FIRST_3,
  RESOURCE_ID_MINUTES_FIRST_4,
  RESOURCE_ID_MINUTES_FIRST_5,
};

static const int MINUTES_LAST_DIGITS[10] = {
  RESOURCE_ID_MINUTES_LAST_0,
  RESOURCE_ID_MINUTES_LAST_1,
  RESOURCE_ID_MINUTES_LAST_2,
  RESOURCE_ID_MINUTES_LAST_3,
  RESOURCE_ID_MINUTES_LAST_4,
  RESOURCE_ID_MINUTES_LAST_5,
  RESOURCE_ID_MINUTES_LAST_6,
  RESOURCE_ID_MINUTES_LAST_7,
  RESOURCE_ID_MINUTES_LAST_8,
  RESOURCE_ID_MINUTES_LAST_9,
};
  
static void init_time_struct(struct tm ** time_struct) {
  if(!*time_struct) {
    time_t now = time(NULL);
    *time_struct = localtime(&now);
  }
}

uint32_t hours_first_digit(struct tm * time_struct) {
  init_time_struct(&time_struct);
  return HOURS_FIRST_DIGITS[time_struct->tm_hour / 10];
}

uint32_t hours_last_digit(struct tm * time_struct) {
  init_time_struct(&time_struct);
  return HOURS_LAST_DIGITS[time_struct->tm_hour % 10];
}

uint32_t minutes_first_digit(struct tm * time_struct) {
  init_time_struct(&time_struct);
  return MINUTES_FIRST_DIGITS[time_struct->tm_min / 10];
}

uint32_t minutes_last_digit(struct tm * time_struct) {
  init_time_struct(&time_struct);
  return MINUTES_LAST_DIGITS[time_struct->tm_min % 10];
}