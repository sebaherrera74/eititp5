
#include <stdint.h>
#include "clock.h"
#include <string.h>

struct clock_s {
    uint8_t time[6];
    bool valid;
};

static struct clock_s instances;


clock_t ClockCreate(uint16_t ticks_per_seconds){
    instances.valid=false;
    memset(instances.time,0,6);
    return &instances;
}

bool ClockGetTime(clock_t clock,uint8_t * time,uint8_t size){
    //memset(time,0,size);
    memcpy(time,clock->time,size);
    return clock->valid;
}


void ClockSetupTime(clock_t clock,uint8_t * time,uint8_t size){
     memcpy(clock->time,time,size);
    clock->valid=true;
}