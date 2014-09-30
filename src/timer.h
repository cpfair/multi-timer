#pragma once

#include <pebble.h>

typedef enum {
  TIMER_TYPE_TIMER = 0,
  TIMER_TYPE_STOPWATCH = 1
} TimerType;

typedef enum {
  TIMER_VIBE_SINGLE = 0
} TimerVibration;

typedef struct Timer {
  uint16_t id;
  TimerType type;
  uint16_t duration;
  uint16_t time_left;
  TimerVibration vibration;
  uint8_t repeat;
  uint8_t repeat_count;
} Timer;

