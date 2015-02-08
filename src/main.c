#include <pebble.h>
#include "settings.h"
#include "digits.h"
#include "digit_bitmaps.h"
#include "symmetry.h"
#include "positions.h"

typedef struct  DisplayState {
  GColor bgcolor;
  uint8_t digits[4];
  bool steel_offset;
  bool inverted;
  bool symmetry;
  bool melt;
  bool pm_dot;
} DisplayState;

static DisplayState* state;
static Settings *settings;
static Window *window;
static Layer *canvas;
static InverterLayer *inverter;

void update_screen() {
  bool hour24;
  if (settings->time_display == TimeDispModeAuto) {
    hour24 = clock_is_24h_style();
  } else {
    hour24 = settings->time_display == TimeDispMode24H;
  }

  state->digits[0] = hours_first_digit(NULL, hour24);
  state->digits[1] = hours_last_digit(NULL, hour24);
  state->digits[2] = minutes_first_digit(NULL);
  state->digits[3] = minutes_last_digit(NULL);

  state->symmetry = settings->screen_mode != ScreenModeSimple;
  state->inverted = settings->bgcolor == GColorWhite;
  if (settings->steel_offset == SteelOffsetAuto) {
    state->steel_offset = watch_info_get_model() == WATCH_INFO_MODEL_PEBBLE_STEEL;
  } else {
    state->steel_offset = settings->steel_offset;
  }

  layer_mark_dirty(canvas);
  layer_set_hidden(inverter_layer_get_layer(inverter), !state->inverted);
  layer_mark_dirty(inverter_layer_get_layer(inverter));
}

static void update_canvas(struct Layer *layer, GContext *ctx) {
  graphics_context_set_compositing_mode(ctx, GCompOpAssignInverted);
  for (int i = 0; i < 4; i++) {
    graphics_draw_bitmap_in_rect(ctx, get_digit_bitmap(i, state->digits[i]), get_digit_position(i, state->steel_offset));
    if (state->symmetry) {
      GBitmap* symmetric = get_digit_symmetry_bitmap(i, state->digits[i], HorizontalSym);
      graphics_draw_bitmap_in_rect(ctx, symmetric, get_symmetric_position(i, state->steel_offset));
      gbitmap_destroy(symmetric);
    }
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
  free_digit_bitmaps();
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_screen();
}

static void in_recv_handler(DictionaryIterator *received, void *context) {
  settings->bgcolor = (GColor) dict_find(received, APPKEY_BGCOLOR)->value->int32;
  settings->screen_mode = (ScreenMode) dict_find(received, APPKEY_DISPLAY)->value->int32;
  settings->time_display = (TimeDisplayMode) dict_find(received, APPKEY_HOUR24)->value->int32;
  settings->steel_offset = (SteelOffset) dict_find(received, APPKEY_STEEL_OFFSET)->value->int32;

  update_screen();
}

static void init(void) {
  settings = settings_create();
  persist_read_settings(settings);
  state = malloc(sizeof(DisplayState));

  // React to settings message from phone
  app_message_register_inbox_received(in_recv_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true);

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit(void) {
  window_destroy(window);

  persist_write_settings(settings);
  settings_destroy(settings);
  free(state);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
