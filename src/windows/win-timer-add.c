#include <pebble.h>
#include <pebble-assist.h>
#include "win-timer-add.h"

static void window_load(Window* window);
static void window_unload(Window* window);
static void layer_update(Layer* layer, GContext* ctx);

static Window* window;
static Layer* layer;

void win_timer_add_init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });
}

void win_timer_add_show(void) {
  window_stack_push(window, false);
}

static void window_load(Window* window) {
  layer = layer_create_fullscreen(window);
  layer_set_update_proc(layer, layer_update);
  layer_add_to_window(layer, window);
}

static void window_unload(Window* window) {
  layer_destroy(layer);
}

static void layer_update(Layer* layer, GContext* ctx) {
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_context_set_text_color(ctx, GColorBlack);
  graphics_draw_text(ctx, ":", fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), GRect(70, 4, 5, 28), GTextOverflowModeFill, GTextAlignmentCenter, NULL);
  graphics_fill_rect(ctx, GRect(33, 8, 32, 32), 2, GCornersAll);
  graphics_fill_rect(ctx, GRect(80, 8, 32, 32), 2, GCornersAll);
  graphics_context_set_text_color(ctx, GColorWhite);
  graphics_draw_text(ctx, "15", fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), GRect(33, 5, 32, 28), GTextOverflowModeFill, GTextAlignmentCenter, NULL);
  graphics_draw_text(ctx, "23", fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD), GRect(80, 5, 32, 28), GTextOverflowModeFill, GTextAlignmentCenter, NULL);

  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(8, 48, 128, 22), 2, GCornersAll);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(9, 49, 126, 20), 2, GCornersAll);
  graphics_context_set_text_color(ctx, GColorBlack);
  graphics_draw_text(ctx, "Vibrate Once", fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(8, 46, 128, 18), GTextOverflowModeFill, GTextAlignmentCenter, NULL);

  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(8, 78, 128, 22), 2, GCornersAll);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(9, 79, 126, 20), 2, GCornersAll);
  graphics_context_set_text_color(ctx, GColorBlack);
  graphics_draw_text(ctx, "Don't Repeat", fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(8, 76, 128, 18), GTextOverflowModeFill, GTextAlignmentCenter, NULL);

  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, GRect(8, 118, 128, 26), 2, GCornersAll);
  graphics_context_set_text_color(ctx, GColorWhite);
  graphics_draw_text(ctx, "Add Timer", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(8, 114, 128, 24), GTextOverflowModeFill, GTextAlignmentCenter, NULL);
}
