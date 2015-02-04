#include <pebble.h>
#include "dimensions.h"
#include "digits.h"
#include "settings.h"

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
static Layer *symmetry_layer;

static GPoint screen_center() {
  GRect bounds = layer_get_bounds(window_get_root_layer(window));
  switch(watch_info_get_model()) {
    case WATCH_INFO_MODEL_PEBBLE_STEEL:
      return GPoint(bounds.size.w/2, 95);
    default:
      return grect_center_point(&bounds);
  }
}

static GColor bg_color;
static int display;
static void load_config() {
  bg_color = -1;
  if (persist_exists(KEY_BGCOLOR)) {
    bg_color = persist_read_int(KEY_BGCOLOR);
  }
  if (bg_color == -1) {
    //TODO check watch color
    bg_color = GColorBlack;
  }
  display = 1;
  if (persist_exists(KEY_DISPLAY)) {
    display = persist_read_int(KEY_DISPLAY);
  }
}
static void save_config() {
  persist_write_int(KEY_BGCOLOR, bg_color);
  persist_write_int(KEY_DISPLAY, display);
}

static GColor fg_color;
static GCompOp compositing;
static void init_colors() {
  if (bg_color == GColorBlack) {
    fg_color = GColorWhite;
    compositing = GCompOpAssignInverted;
  } else {
    fg_color = GColorBlack;
    compositing = GCompOpAssign;
  }
}

static void symmetry_layer_update_proc(struct Layer *layer, GContext *ctx) {
  
  GBitmap* frame_buffer = graphics_capture_frame_buffer(ctx);
  uint8_t *image = frame_buffer->addr;
  uint16_t lines = frame_buffer->bounds.size.h;
  uint16_t cols = frame_buffer->bounds.size.w;

  uint8_t * symmetry_data = malloc(lines * frame_buffer->row_size_bytes);
  
  uint8_t curr_byte = 0;
  uint16_t line_byte_offset;
  int16_t col_orig, col_sym;

  for (uint16_t l = 0; l < lines; l++) {
    line_byte_offset = l * frame_buffer->row_size_bytes;

    for (col_sym = 0; col_sym < cols; col_sym++) {
      col_orig = cols - col_sym - 1;

      if(fg_color == ((image[line_byte_offset + col_orig/8] >> (col_orig%8)) & 1)) {
        curr_byte += 1 << (col_sym%8);
      }
      if ((col_sym+1)%8 == 0) {
        symmetry_data[line_byte_offset + col_sym/8] = curr_byte;
        curr_byte = 0;
      }
    }
    symmetry_data[line_byte_offset + col_sym/8] = curr_byte; // Last byte in a row
  }
  
  graphics_release_frame_buffer(ctx, frame_buffer);
  graphics_context_set_stroke_color(ctx, fg_color);

  for (uint16_t l = 0; l < lines; l++) {
    uint32_t line_byte_offset = l * frame_buffer->row_size_bytes;
    for (uint16_t c = 0; c < cols; c++) {
      uint32_t total_byte_offset = line_byte_offset + c/8;
      if ((symmetry_data[total_byte_offset] >> (c%8)) & 1) {
        graphics_draw_pixel(ctx, GPoint(c, l));
      }
    }
  }
  free(symmetry_data);
}

static void update_time() {
  if(hours_first_bitmap) gbitmap_destroy(hours_first_bitmap);
  hours_first_bitmap = gbitmap_create_with_resource(hours_first_digit(NULL));
  bitmap_layer_set_bitmap(hours_first_layer, hours_first_bitmap);
  layer_mark_dirty(bitmap_layer_get_layer(hours_first_layer));
  
  if(hours_last_bitmap) gbitmap_destroy(hours_last_bitmap);
  hours_last_bitmap = gbitmap_create_with_resource(hours_last_digit(NULL));
  bitmap_layer_set_bitmap(hours_last_layer, hours_last_bitmap);
  layer_mark_dirty(bitmap_layer_get_layer(hours_last_layer));

  if(minutes_first_bitmap) gbitmap_destroy(minutes_first_bitmap);
  minutes_first_bitmap = gbitmap_create_with_resource(minutes_first_digit(NULL));
  bitmap_layer_set_bitmap(minutes_first_layer, minutes_first_bitmap);
  layer_mark_dirty(bitmap_layer_get_layer(minutes_first_layer));
  
  if(minutes_last_bitmap) gbitmap_destroy(minutes_last_bitmap);
  minutes_last_bitmap = gbitmap_create_with_resource(minutes_last_digit(NULL));
  bitmap_layer_set_bitmap(minutes_last_layer, minutes_last_bitmap);
  layer_mark_dirty(bitmap_layer_get_layer(minutes_last_layer));

  if(symmetry_layer) layer_mark_dirty(symmetry_layer);
}

static void window_load(Window *window) {
  init_colors();
  
  window_set_background_color(window, bg_color);
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  GPoint center = screen_center();
  main_layer = layer_create(GRect(
    center.x - MAIN_LAYER_WIDTH/2,
    center.y - MAIN_LAYER_HEIGHT/2,
    MAIN_LAYER_WIDTH,
    MAIN_LAYER_HEIGHT
  ));
  layer_add_child(window_layer, main_layer);

  hours_first_layer = bitmap_layer_create(GRect(
    HOURS_FIRST_X, HOURS_FIRST_Y,
    HOURS_FIRST_WIDTH, HOURS_FIRST_HEIGHT
  ));
  bitmap_layer_set_compositing_mode(hours_first_layer, compositing);
  layer_add_child(main_layer, bitmap_layer_get_layer(hours_first_layer));

  hours_last_layer = bitmap_layer_create(GRect(
    HOURS_LAST_X, HOURS_LAST_Y,
    HOURS_LAST_WIDTH, HOURS_LAST_HEIGHT
  ));
  bitmap_layer_set_compositing_mode(hours_last_layer, compositing);
  layer_add_child(main_layer, bitmap_layer_get_layer(hours_last_layer));

  minutes_first_layer = bitmap_layer_create(GRect(
    MINUTES_FIRST_X, MINUTES_FIRST_Y,
    MINUTES_FIRST_WIDTH, MINUTES_FIRST_HEIGHT
  ));
  bitmap_layer_set_compositing_mode(minutes_first_layer, compositing);
  layer_add_child(main_layer, bitmap_layer_get_layer(minutes_first_layer));

  minutes_last_layer = bitmap_layer_create(GRect(
    MINUTES_LAST_X, MINUTES_LAST_Y,
    MINUTES_LAST_WIDTH, MINUTES_LAST_HEIGHT
  ));
  bitmap_layer_set_compositing_mode(minutes_last_layer, compositing);
  layer_add_child(main_layer, bitmap_layer_get_layer(minutes_last_layer));

  if (display > 0) {
    symmetry_layer = layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
    layer_add_child(window_layer, symmetry_layer);
    layer_set_update_proc(symmetry_layer, symmetry_layer_update_proc);
  }

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
  if(symmetry_layer) layer_destroy(symmetry_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void in_recv_handler(DictionaryIterator *received, void *context) {
  bg_color = (GColor) dict_find(received, KEY_BGCOLOR)->value->int32;
  display = dict_find(received, KEY_DISPLAY)->value->int32;
}

static void init(void) {
  load_config();

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

  save_config();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
