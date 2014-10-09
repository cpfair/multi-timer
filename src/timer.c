#include <pebble.h>
#include "timers.h"
#include "timer.h"

static void timer_tick(void* context);
static void timer_finish(Timer* timer);
static void timer_schedule_tick(Timer* timer);
static void timer_cancel_tick(Timer* timer);
static void timer_schedule_wakeup(Timer* timer);
static void timer_cancel_wakeup(Timer* timer);

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
  timer_schedule_wakeup(timer);
  timers_mark_updated();
}

void timer_pause(Timer* timer) {
  timer->status = TIMER_STATUS_PAUSED;
  timer_cancel_tick(timer);
  timer_cancel_wakeup(timer);
  timers_mark_updated();
}

void timer_resume(Timer* timer) {
  timer->status = TIMER_STATUS_RUNNING;
  timer_schedule_tick(timer);
  timer_schedule_wakeup(timer);
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
      if (timer->current_time <= 0) {
        timer_finish(timer);
      }
      break;
  }
  if (timer->status == TIMER_STATUS_RUNNING) {
    timer_schedule_tick(timer);
  }
  timers_mark_updated();
}

static void timer_finish(Timer* timer) {
  timer->status = TIMER_STATUS_DONE;
}

static void timer_schedule_tick(Timer* timer) {
  timer_cancel_tick(timer);
  timer->timer = app_timer_register(1000, timer_tick, (void*)timer);
}

static void timer_cancel_tick(Timer* timer) {
  if (! timer) {
    return;
  }
  if (timer->timer) {
    app_timer_cancel(timer->timer);
    timer->timer = NULL;
  }
}

static void timer_schedule_wakeup(Timer* timer) {
  if (! timer) {
    return;
  }
  timer_cancel_wakeup(timer);
  time_t wakeup_time = time(NULL);
  wakeup_time += timer->current_time;
  timer->wakeup_id = wakeup_schedule(wakeup_time, timer->id, false);
}

static void timer_cancel_wakeup(Timer* timer) {
  if (! timer) {
    return;
  }
  if (timer->wakeup_id <= 0) {
    return;
  }
  wakeup_cancel(timer->wakeup_id);
  timer->wakeup_id = 0;
}
