#include <pebble.h>
#include <linked-list.h>
// #include <pebble-assist.h>
#include "timer.h"
#include "timers.h"

static void timers_cleanup(void);
static bool timer_id_compare(Timer* timer1, Timer* timer2);

LinkedRoot* timers = NULL;
LinkedRoot* update_handlers = NULL;

void timers_init(void) {
  timers_cleanup();
  timers = linked_list_create_root();
  update_handlers = linked_list_create_root();
}

uint8_t timers_count(void) {
  return linked_list_count(timers);
}

Timer* timers_get(uint8_t index) {
  if (! timers) {
    return NULL;
  }
  return linked_list_get(timers, index);
}

Timer* timers_find(uint16_t id) {
  uint8_t count = timers_count();
  for (uint8_t c = 0; c < count; c += 1) {
    Timer* timer = timers_get(c);
    if (timer->id == id) {
      return timer;
    }
  }
  return NULL;
}

bool timers_add(Timer* timer) {
  linked_list_append(timers, timer);
  return true;
}

bool timers_remove(uint16_t position) {
  Timer* timer = timers_get(position);
  if (NULL == timer) {
    return false;
  }
  linked_list_remove(timers, position);
  free(timer);
  return true;
}

void timers_mark_updated(void) {
  uint8_t handler_count = linked_list_count(update_handlers);
  for (uint8_t h = 0; h < handler_count; h += 1) {
    TimersUpdatedHandler handler = linked_list_get(update_handlers, h);
    handler();
  }
}

void timers_register_update_handler(TimersUpdatedHandler handler) {
  linked_list_append(update_handlers, handler);
}

static void timers_cleanup(void) {
  if (timers) {
    return;
  }
  while (linked_list_count(timers) > 0) {
    Timer* timer = (Timer*) linked_list_get(timers, 0);
    linked_list_remove(timers, 0);
    free(timer);
  }
  free(timers);
  timers = NULL;
}

static bool timer_id_compare(Timer* timer1, Timer* timer2) {
  return timer1->id == timer2->id;
}