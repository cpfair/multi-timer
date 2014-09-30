#include <pebble.h>
#include "windows/win-main.h"
#include "timers.h"

static void init(void);
static void deinit(void);

int main(void) {
  init();
  app_event_loop();
  deinit();
}

static void init(void) {
  timers_init();

  win_main_init();

  win_main_show();
}

static void deinit(void) {
}