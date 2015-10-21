#include <pebble.h>
#include "settings.h"
#include "digits.h"
#include "digit_bitmaps.h"
/*#include "melted_bitmaps.h"*/
#include "symmetry.h"
#include "positions.h"
#include "effect_layer/effect_layer.h"

typedef struct DisplayState {
  uint8_t digits[4];
  bool steel_offset;
  bool bt_connected;
  bool inverted;
  bool symmetry;
  bool melted;
  bool pm_dot;
} DisplayState;

static DisplayState* state;
static Settings *settings;
static Window *window;
static Layer *canvas;
static InverterLayer *inverter;
static GBitmap* digit_bitmaps[4];
static uint8_t loaded_digits[4];

void update_inverter(bool bt_connected) {
  state->bt_connected = bt_connected;
  state->inverted = gcolor_equal(settings->bgcolor, GColorWhite) ^ (!state->bt_connected && settings->bt_invert);
  layer_set_hidden(inverter_layer_get_layer(inverter), !state->inverted);
  layer_mark_dirty(inverter_layer_get_layer(inverter));
}

void update_screen() {
  bool hour24;
  if (settings->time_display == TimeDispModeAuto) {
    hour24 = clock_is_24h_style();
  } else {
    hour24 = settings->time_display == TimeDispMode24H;
  }

  time_t now = time(NULL);
  struct tm * tm_now = localtime(&now);

  for (int i = 0; i < 4; i++) {
    state->digits[i] = get_time_digit(i, tm_now, hour24);
  }

  state->symmetry = settings->screen_mode != ScreenModeSimple;
  state->melted = settings->screen_mode == ScreenModeInsane;
  if (settings->steel_offset == SteelOffsetAuto) {
    state->steel_offset = watch_info_get_model() == WATCH_INFO_MODEL_PEBBLE_STEEL;
  } else {
    state->steel_offset = settings->steel_offset;
  }

  layer_mark_dirty(canvas);
  update_inverter(bluetooth_connection_service_peek());
}

static void update_canvas(struct Layer *layer, GContext *ctx) {
  graphics_context_set_compositing_mode(ctx, GCompOpSet);
  for (int i = 0; i < 4; i++) {

    if (!(loaded_digits[i] == state->digits[i] && digit_bitmaps[i])) {
      if(digit_bitmaps[i]) {
        gbitmap_destroy(digit_bitmaps[i]);
      }
      digit_bitmaps[i] = get_digit_bitmap(i, state->digits[i]);
      loaded_digits[i] = state->digits[i];
    }
    graphics_draw_bitmap_in_rect(ctx, digit_bitmaps[i], get_digit_position(i, state->steel_offset));

    /*if (state->melted) {*/
      /*draw_melted_parts(i, state->digits[i], ctx, state->steel_offset);*/
    /*}*/

  }
  if (state->symmetry) {
    GBitmap* buffer = graphics_capture_frame_buffer(ctx);
    GRect bounds = gbitmap_get_bounds(buffer);
    GBitmap* symmetric = gbitmap_create_by_symmetry(buffer, HorizontalSym);
    graphics_release_frame_buffer(ctx, buffer);
    graphics_context_set_compositing_mode(ctx, GCompOpOr);
    graphics_draw_bitmap_in_rect(ctx, symmetric, bounds);
    gbitmap_destroy(symmetric);
  }
}

static void window_load(Window *window) {
  window_set_background_color(window, GColorBlack);
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  canvas = layer_create(bounds);
  layer_set_update_proc(canvas, update_canvas);
  layer_add_child(window_layer, canvas);

  inverter = inverter_layer_create(bounds);
  layer_add_child(window_layer, inverter_layer_get_layer(inverter));

  update_screen();
}

static void window_unload(Window *window) {
  layer_destroy(canvas);
  inverter_layer_destroy(inverter);
  for (int i = 0; i < 4; i++) {
    if(digit_bitmaps[i]) gbitmap_destroy(digit_bitmaps[i]);
  }
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_screen();
  if (units_changed & HOUR_UNIT && settings->hour_vibes) vibes_double_pulse();
}

static void in_recv_handler(DictionaryIterator *received, void *context) {
  settings->bgcolor = dict_find(received, APPKEY_BGCOLOR)->value->int32 == 1 ? GColorBlack : GColorWhite;
  settings->screen_mode = (ScreenMode) dict_find(received, APPKEY_DISPLAY)->value->int32;
  settings->time_display = (TimeDisplayMode) dict_find(received, APPKEY_HOUR24)->value->int32;
  settings->steel_offset = (SteelOffset) dict_find(received, APPKEY_STEEL_OFFSET)->value->int32;
  settings->bt_invert = (bool) dict_find(received, APPKEY_BT_INVERT)->value->int32;
  settings->bt_vibes = (bool) dict_find(received, APPKEY_BT_VIBES)->value->int32;
  settings->hour_vibes = (bool) dict_find(received, APPKEY_HOUR_VIBES)->value->int32;

  update_screen();
}

static void bt_handler(bool connected) {
  update_inverter(connected);
  if (!connected && settings->bt_vibes) vibes_long_pulse();
}

static void init(void) {
  settings = settings_create();
  persist_read_settings(settings);
  state = malloc(sizeof(DisplayState));

  // React to settings message from phone
  app_message_register_inbox_received(in_recv_handler);
  app_message_open(1 + (7+sizeof(uint32_t)) * APPKEY_COUNT, 0);

  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true);

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  bluetooth_connection_service_subscribe(bt_handler);
}

static void deinit(void) {
  window_destroy(window);

  destroy_sprite();
  persist_write_settings(settings);
  settings_destroy(settings);
  free(state);
  bluetooth_connection_service_unsubscribe();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
