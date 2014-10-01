#include <pebble.h>
#include "timers.h"
#include "timer.h"

static void timer_tick(void* context);
static void timer_schedule_tick(Timer* timer);

void timer_time_str(Timer* timer, bool showHours, char* str, int str_len) {
  int hours = timer->current_time / 3600;
  int minutes = (showHours ? (timer->current_time % 3600) : timer->current_time) / 60;
  int seconds = (showHours ? (timer->current_time % 3600) : timer->current_time) % 60;
  if (showHours) {
    snprintf(str, str_len, "%02d:%02d:%02d", hours, minutes, seconds);
  }
  else {
    snprintf(str, str_len, "%02d:%02d", minutes, seconds);
  }
}

void timer_start(Timer* timer) {
  switch (timer->type) {
    case TIMER_TYPE_TIMER:
      timer->current_time = timer->length;
      break;
    case TIMER_TYPE_STOPWATCH:
      timer->current_time = 0;
      break;
  }
  timer->status = TIMER_STATUS_RUNNING;
  timer_schedule_tick(timer);
  timers_mark_updated();
}

void timer_pause(Timer* timer) {
  timer->status = TIMER_STATUS_PAUSED;
  timers_mark_updated();
}

void timer_resume(Timer* timer) {
  timer->status = TIMER_STATUS_RUNNING;
  timers_mark_updated();
}

void timer_reset(Timer* timer) {
  switch (timer->type) {
    case TIMER_TYPE_TIMER:
      timer->current_time = timer->length;
      break;
    case TIMER_TYPE_STOPWATCH:
      timer->current_time = 0;
      break;
  }
  timer->status = TIMER_STATUS_STOPPED;
  timers_mark_updated();
}

static void timer_tick(void* context) {
  Timer* timer = (Timer*)context;
  timer->timer = NULL;
  switch (timer->type) {
    case TIMER_TYPE_STOPWATCH:
      timer->current_time += 1;
      break;
    case TIMER_TYPE_TIMER:
      timer->current_time -= 1;
      break;
  }
  if (timer->status == TIMER_STATUS_RUNNING) {
    timer_schedule_tick(timer);
  }
  timers_mark_updated();
}

static void timer_schedule_tick(Timer* timer) {
  if (timer->timer) {
    app_timer_cancel(timer->timer);
    timer->timer = NULL;
  }
  timer->timer = app_timer_register(1000, timer_tick, (void*)timer);
}