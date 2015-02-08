#include <pebble.h>
#include "settings.h"
#include "digits.h"
#include "symmetry.h"
#include "positions.h"


static Settings *settings;
static Window *window;
static Layer *main_layer;
static BitmapLayer* digit_layers[4];
static BitmapLayer* symmetric_layers[4];

static GPoint screen_center() {
  GRect bounds = layer_get_bounds(window_get_root_layer(window));
  switch(watch_info_get_model()) {
    case WATCH_INFO_MODEL_PEBBLE_STEEL:
      return GPoint(bounds.size.w/2, 95);
    default:
      return grect_center_point(&bounds);
  }
}

static bool hour24_mode() {
  if (settings->time_display == TimeDispModeAuto) {
    return clock_is_24h_style();
  } else {
    return settings->time_display == TimeDispMode24H;
  }
}

static GColor fg_color;
static GCompOp compositing;

static void update_time() {
  uint8_t digits[4] = {
    hours_first_digit(NULL, hour24_mode()),
    hours_last_digit(NULL, hour24_mode()),
    minutes_first_digit(NULL),
    minutes_last_digit(NULL),
  };

  for (int i = 0; i < 4; i++) {
    bitmap_layer_set_bitmap(digit_layers[i], get_digit_bitmap(i, digits[i]));
    bitmap_layer_set_bitmap(symmetric_layers[i], get_digit_symmetry_bitmap(i, digits[i], HorizontalSym));
    layer_mark_dirty(bitmap_layer_get_layer(digit_layers[i]));
    layer_mark_dirty(bitmap_layer_get_layer(symmetric_layers[i]));
  }
}

static void refresh_display_options() {
  if (settings->bgcolor == GColorBlack) {
    fg_color = GColorWhite;
    compositing = GCompOpAssignInverted;
  } else {
    fg_color = GColorBlack;
    compositing = GCompOpAssign;
  }
  window_set_background_color(window, settings->bgcolor);

  for (int i = 0; i < 4; i++) {
    bitmap_layer_set_compositing_mode(digit_layers[i], compositing);
    bitmap_layer_set_compositing_mode(symmetric_layers[i], compositing);
  }
}

static void window_load(Window *window) {
  window_set_background_color(window, settings->bgcolor);
  Layer *window_layer = window_get_root_layer(window);

  GPoint center = screen_center();
  main_layer = layer_create(GRect(
    center.x - get_main_layer_size().w/2,
    center.y - get_main_layer_size().h/2,
    get_main_layer_size().w,
    get_main_layer_size().h
  ));
  layer_add_child(window_layer, main_layer);

  for (int i = 0; i < 4; i++) {
    digit_layers[i] = bitmap_layer_create(get_digit_position(i));
    layer_add_child(main_layer, bitmap_layer_get_layer(digit_layers[i]));

    symmetric_layers[i] = bitmap_layer_create(get_symmetric_position(i));
    layer_add_child(main_layer, bitmap_layer_get_layer(symmetric_layers[i]));
  }

  refresh_display_options();
  update_time();
}

static void window_unload(Window *window) {
  layer_destroy(main_layer);
  free_digit_bitmaps();
  for (int i = 0; i < 4; i++) {
    bitmap_layer_destroy(digit_layers[i]);
    bitmap_layer_destroy(symmetric_layers[i]);
  }
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void in_recv_handler(DictionaryIterator *received, void *context) {
  settings->bgcolor = (GColor) dict_find(received, APPKEY_BGCOLOR)->value->int32;
  settings->screen_mode = dict_find(received, APPKEY_DISPLAY)->value->int32;
  settings->time_display = dict_find(received, APPKEY_HOUR24)->value->int32;

  refresh_display_options();
  update_time();
}

static void init(void) {
  settings = settings_create();
  persist_read_settings(settings);
  init_positions();

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
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
