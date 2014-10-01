#include <pebble.h>
#include "timer.h"

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
}

void timer_pause(Timer* timer) {
  timer->status = TIMER_STATUS_PAUSED;
}

void timer_resume(Timer* timer) {
  timer->status = TIMER_STATUS_RUNNING;
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
}