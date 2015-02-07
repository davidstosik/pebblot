#define APPKEY_BGCOLOR 0
#define APPKEY_DISPLAY 1
#define APPKEY_HOUR24  2

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

struct SettingsStruct {
  GColor            bgcolor;
  ScreenMode        screen_mode;
  TimeDisplayMode   time_display;
};
typedef struct SettingsStruct Settings;

Settings* settings_create();
void settings_destroy(Settings* settings);
void persist_read_settings(Settings* settings);
void persist_write_settings(Settings* settings);
