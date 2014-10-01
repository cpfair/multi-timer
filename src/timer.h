#pragma once

#include <pebble.h>

typedef enum {
  TIMER_TYPE_TIMER = 0,
  TIMER_TYPE_STOPWATCH = 1,
} TimerType;

typedef enum {
  TIMER_VIBE_SINGLE = 0,
} TimerVibration;

typedef enum {
  TIMER_STATUS_STOPPED = 0,
  TIMER_STATUS_RUNNING = 1,
  TIMER_STATUS_PAUSED = 2,
  TIMER_STATUS_DONE = 3,
} TimerStatus;

typedef struct Timer {
  uint16_t id;
  TimerType type;
  uint16_t length;
  uint16_t current_time;
  TimerStatus status;
  TimerVibration vibration;
  uint8_t repeat;
  uint8_t repeat_count;
  AppTimer* timer;
} Timer;

void timer_time_str(Timer* timer, bool showHours, char* str, int str_len);
void timer_start(Timer* timer);
void timer_pause(Timer* timer);
void timer_resume(Timer* timer);
void timer_reset(Timer* timer);