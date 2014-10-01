#include <pebble.h>
#include "win-timer-add.h"

static Window* window;

void win_timer_add_init(void) {
  window = window_create();
}

void win_timer_add_show(void) {
  window_stack_push(window, false);
}