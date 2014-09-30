#include <pebble.h>
#include <pebble-assist.h>
#include "../timers.h"

#define MENU_SECTION_TIMERS 0
#define MENU_SECTION_OTHER 1

#define MENU_ROW_COUNT_OTHER 1

#define MENU_ROW_OTHER_ADD 0

static void window_load(Window* window);
static void window_unload(Window* window);
static uint16_t menu_num_rows(struct MenuLayer* menu_layer, uint16_t section_index, void* callback_context);
static uint16_t menu_num_sections(struct MenuLayer* menu_layer, void* callback_context);
static void menu_draw_row(GContext* ctx, const Layer* cell_layer, MenuIndex* cell_index, void* callback_context);
static void menu_draw_row_timers(GContext* ctx, const Layer* cell_layer, uint16_t row_index);
static void menu_draw_row_other(GContext* ctx, const Layer* cell_layer, uint16_t row_index);
static void menu_select(struct MenuLayer* menu_layer, MenuIndex* cell_index, void* callback_context);
static void menu_select_timers(uint16_t row_index);
static void menu_select_other(uint16_t row_index);

static Window* window;
static MenuLayer* menu_layer;

void win_main_init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });
}

void win_main_show(void) {
  window_stack_push(window, false);
}

void win_main_cleanup(void) {
  window_destroy(window);
}

//

static void window_load(Window* window) {
  menu_layer = menu_layer_create_fullscreen(window);
  menu_layer_set_click_config_onto_window(menu_layer, window);
  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks) {
    .get_num_rows = menu_num_rows,
    .get_num_sections = menu_num_sections,
    .draw_row = menu_draw_row,
    .select_click = menu_select,
  });
  menu_layer_add_to_window(menu_layer, window);
}

static void window_unload(Window* window) {

}

static uint16_t menu_num_rows(struct MenuLayer* menu_layer, uint16_t section_index, void* callback_context) {
  switch (section_index) {
    case MENU_SECTION_TIMERS:
      return timers_count();
    case MENU_SECTION_OTHER:
      return MENU_ROW_COUNT_OTHER;
  }
  return 0;
}

static uint16_t menu_num_sections(struct MenuLayer* menu_layer, void* callback_context) {
  return 2;
}

static void menu_draw_row(GContext* ctx, const Layer* cell_layer, MenuIndex* cell_index, void* callback_context) {
  switch (cell_index->section) {
    case MENU_SECTION_TIMERS:
      menu_draw_row_timers(ctx, cell_layer, cell_index->row);
      break;
    case MENU_SECTION_OTHER:
      menu_draw_row_other(ctx, cell_layer, cell_index->row);
      break;
  }
}

static void menu_draw_row_timers(GContext* ctx, const Layer* cell_layer, uint16_t row_index) {

}

static void menu_draw_row_other(GContext* ctx, const Layer* cell_layer, uint16_t row_index) {
  switch (row_index) {
    case MENU_ROW_OTHER_ADD:
      menu_cell_title_draw(ctx, cell_layer, "Add Timer");
      break;
  }
}

static void menu_select(struct MenuLayer* menu_layer, MenuIndex* cell_index, void* callback_context) {
  switch (cell_index->section) {
    case MENU_SECTION_TIMERS:
      menu_select_timers(cell_index->row);
      break;
    case MENU_SECTION_OTHER:
      menu_select_other(cell_index->row);
      break;
  }
}

static void menu_select_timers(uint16_t row_index) {

}

static void menu_select_other(uint16_t row_index) {

}