#include <pebble.h>
#include "settings.h"

size_t sizeof_settings() {
  return sizeof(Settings);
}

Settings* settings_create() {
  Settings* settings = malloc(sizeof_settings());
  settings->bgcolor = GColorWhite;
  settings->screen_mode = ScreenModeSymmetry;
  settings->time_display = TimeDispModeAuto;
  settings->steel_offset = SteelOffsetAuto;
  settings->bt_invert = true;
  settings->bt_vibes = true;
  settings->hour_vibes = true;
  return settings;
}

void settings_destroy(Settings* settings) {
  free(settings);
}

void persist_read_settings(Settings* settings) {
  if (persist_exists(PERSIST_KEY_SETTINGS)) {
    persist_read_data(PERSIST_KEY_SETTINGS, settings, sizeof_settings());
  }
}

void persist_write_settings(Settings* settings) {
  persist_write_data(PERSIST_KEY_SETTINGS, settings, sizeof_settings());
}

