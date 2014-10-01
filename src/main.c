#include <pebble.h>
#include "windows/win-main.h"
#include "timers.h"

static void init(void);
static void deinit(void);

static void create_fake_timers(void);

int main(void) {
  init();
  app_event_loop();
  deinit();
}

static void init(void) {
  timers_init();
  create_fake_timers();

  win_main_init();

  win_main_show();
}

static void deinit(void) {
}

static void create_fake_timers(void) {
  Timer* timer = malloc(sizeof(Timer));
  timer->id = 1;
  timer->type = TIMER_TYPE_TIMER;
  timer->length = timer->current_time = 10 * 60;
  timer->status = TIMER_STATUS_STOPPED;
  timer->repeat = 1;
  timer->repeat_count = 0;
  timer->vibration = TIMER_VIBE_SINGLE;
  timers_add(timer);

  Timer* stopwatch = malloc(sizeof(Timer));
  stopwatch->id = 2;
  stopwatch->type = TIMER_TYPE_STOPWATCH;
  stopwatch->status = TIMER_STATUS_STOPPED;
  stopwatch->current_time = 0;
  timers_add(stopwatch);
}