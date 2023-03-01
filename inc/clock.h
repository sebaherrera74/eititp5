#include <stdint.h>
#include <stdbool.h>

typedef struct clock_s * clock_t;


clock_t ClockCreate(uint16_t ticks_per_seconds);

bool ClockGetTime(clock_t clock,uint8_t * time,uint8_t size);