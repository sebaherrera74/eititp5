#include <stdint.h>
#include <stdbool.h>

typedef struct clock_s * clock_t;

typedef void(*clock_event_t)(clock_t clock,bool enabled);

clock_t ClockCreate(uint16_t ticks_per_seconds,clock_event_t event_handler);

bool ClockGetTime(clock_t clock,uint8_t * time,uint8_t size);

void ClockSetupTime(clock_t clock,const uint8_t * const time,uint8_t size);

void clockNewTick(clock_t clock);

void ClockSetupAlarm(clock_t clock,uint8_t const * const alarm ,uint8_t size);

bool ClockGetAlarm(clock_t clock,uint8_t * alarm,uint8_t size);

bool ClockToggleAlarm(clock_t clock);