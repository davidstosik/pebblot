#define PERSIST_KEY_SETTINGS 0

enum {
  APPKEY_BGCOLOR = 0,
  APPKEY_DISPLAY,
  APPKEY_HOUR24,
  APPKEY_STEEL_OFFSET,
  APPKEY_BT_INVERT,
  APPKEY_BT_VIBES,
  APPKEY_HOUR_VIBES,
  APPKEY_COUNT
};

typedef enum {
  TimeDispModeAuto = -1,
  TimeDispMode12H,
  TimeDispMode24H
} TimeDisplayMode;

typedef enum {
  ScreenModeSimple    = 0,
  ScreenModeSymmetry,
  ScreenModeInsane,
} ScreenMode;

typedef enum {
  SteelOffsetAuto = -1,
  SteelOffsetOff = 0,
  StelOffsetOn = 1,
} SteelOffset;

typedef struct Settings {
  GColor            bgcolor;
  ScreenMode        screen_mode;
  TimeDisplayMode   time_display;
  SteelOffset       steel_offset;
  bool              bt_invert;
  bool              bt_vibes;
  bool              hour_vibes;
} Settings;

Settings* settings_create();
void settings_destroy(Settings* settings);
void persist_read_settings(Settings* settings);
void persist_write_settings(Settings* settings);
