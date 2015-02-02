#include <pebble.h>
#include "dimensions.h"
#include "digits.h"

static Window *window;
static Layer *main_layer;
static GBitmap *hours_first_bitmap;
static GBitmap *hours_last_bitmap;
static BitmapLayer *hours_first_layer;
static BitmapLayer *hours_last_layer;
static GBitmap *minutes_first_bitmap;
static GBitmap *minutes_last_bitmap;
static BitmapLayer *minutes_first_layer;
static BitmapLayer *minutes_last_layer;
static InverterLayer *inverter_layer;


// static void main_layer_update_proc(struct Layer *layer, GContext *ctx) {
  
  

  
// }

static void update_time() {
//   layer_mark_dirty(main_layer);
  if(hours_first_bitmap) gbitmap_destroy(hours_first_bitmap);
  hours_first_bitmap = gbitmap_create_with_resource(hours_first_digit(NULL));
  bitmap_layer_set_bitmap(hours_first_layer, hours_first_bitmap);
  
  if(hours_last_bitmap) gbitmap_destroy(hours_last_bitmap);
  hours_last_bitmap = gbitmap_create_with_resource(hours_last_digit(NULL));
  bitmap_layer_set_bitmap(hours_last_layer, hours_last_bitmap);

  if(minutes_first_bitmap) gbitmap_destroy(minutes_first_bitmap);
  minutes_first_bitmap = gbitmap_create_with_resource(minutes_first_digit(NULL));
  bitmap_layer_set_bitmap(minutes_first_layer, minutes_first_bitmap);
  
  if(minutes_last_bitmap) gbitmap_destroy(minutes_last_bitmap);
  minutes_last_bitmap = gbitmap_create_with_resource(minutes_last_digit(NULL));
  bitmap_layer_set_bitmap(minutes_last_layer, minutes_last_bitmap);
  
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  main_layer = layer_create(GRect(
    (bounds.size.w - MAIN_LAYER_WIDTH) / 2,
    (bounds.size.h - MAIN_LAYER_HEIGHT) / 2,
    MAIN_LAYER_WIDTH,
    MAIN_LAYER_HEIGHT
  ));
  layer_add_child(window_layer, main_layer);

//   layer_set_update_proc(main_layer, main_layer_update_proc);
  
  hours_first_bitmap = gbitmap_create_with_resource(hours_first_digit(NULL));
  hours_first_layer = bitmap_layer_create(GRect(
    HOURS_FIRST_X, HOURS_FIRST_Y,
    HOURS_FIRST_WIDTH, HOURS_FIRST_HEIGHT
  ));
  layer_add_child(main_layer, bitmap_layer_get_layer(hours_first_layer));
  
  hours_last_bitmap = gbitmap_create_with_resource(hours_last_digit(NULL));
  hours_last_layer = bitmap_layer_create(GRect(
    HOURS_LAST_X, HOURS_LAST_Y,
    HOURS_LAST_WIDTH, HOURS_LAST_HEIGHT
  ));
  layer_add_child(main_layer, bitmap_layer_get_layer(hours_last_layer));
  
  minutes_first_bitmap = gbitmap_create_with_resource(minutes_first_digit(NULL));
  minutes_first_layer = bitmap_layer_create(GRect(
    MINUTES_FIRST_X, MINUTES_FIRST_Y,
    MINUTES_FIRST_WIDTH, MINUTES_FIRST_HEIGHT
  ));
  layer_add_child(main_layer, bitmap_layer_get_layer(minutes_first_layer));
  
  minutes_last_bitmap = gbitmap_create_with_resource(minutes_last_digit(NULL));
  minutes_last_layer = bitmap_layer_create(GRect(
    MINUTES_LAST_X, MINUTES_LAST_Y,
    MINUTES_LAST_WIDTH, MINUTES_LAST_HEIGHT
  ));
  layer_add_child(main_layer, bitmap_layer_get_layer(minutes_last_layer));

  
  inverter_layer = inverter_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  layer_add_child(window_layer, inverter_layer_get_layer(inverter_layer));
  
  update_time();
}

static void window_unload(Window *window) {
  layer_destroy(main_layer);
  gbitmap_destroy(hours_first_bitmap);
  gbitmap_destroy(hours_last_bitmap);
  gbitmap_destroy(minutes_first_bitmap);
  gbitmap_destroy(minutes_last_bitmap);
  bitmap_layer_destroy(hours_first_layer);
  bitmap_layer_destroy(hours_last_layer);
  bitmap_layer_destroy(minutes_first_layer);
  bitmap_layer_destroy(minutes_last_layer);
  inverter_layer_destroy(inverter_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void init(void) {
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
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
