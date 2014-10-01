#include <pebble.h>
#include "timer.h"

typedef void (*TimersUpdatedHandler)(void);

// Setup the timers module and its associated data objects.
// Must be called before all other operations.
void timers_init(void);

// Returns the number of timers.
uint8_t timers_count(void);

// Gets a single timer given its position.
// Returns NULL if there is no timer at that position.
Timer* timers_get(uint8_t index);

// Gets a single timer given its ID.
// Returns NULL if there is no timer with that ID.
Timer* timers_find(uint16_t id);

// Adds a new timer.
// Returns true if the operation was successful, false otherwise.
bool timers_add(Timer* timer);

// Removes a timer. This will destroy the timer object and all other
// associated memory.
// Returns true if successful, false otherwise (usually because there was
// no timer at that position).
bool timers_remove(uint16_t position);

void timers_mark_updated(void);
void timers_register_update_handler(TimersUpdatedHandler handler);