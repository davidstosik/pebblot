#define APPKEY_BGCOLOR 0
#define APPKEY_DISPLAY 1
#define APPKEY_HOUR24  2
#define APPKEY_STEEL_OFFSET 3
#define APPKEY_BT_INVERT 4
#define APPKEY_BT_VIBES 5

#define PERSIST_KEY_SETTINGS 0

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
} Settings;

Settings* settings_create();
void settings_destroy(Settings* settings);
void persist_read_settings(Settings* settings);
void persist_write_settings(Settings* settings);
