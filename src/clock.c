
#include <stdint.h>
#include "clock.h"
#include <string.h>


#define TIME_SIZE 6
#define START_VALUE 0
#define SECUNDS_UNIT 5 //pOSICION DE LA UNIDAD DE SEGUNDOS
struct clock_s {
    uint8_t time[TIME_SIZE];
    bool valid;
    uint16_t ticks_per_seconds;
    uint16_t ticks_count;
};

static struct clock_s instances;


clock_t ClockCreate(uint16_t ticks_per_seconds){
    instances.valid=false;
    memset(instances.time,START_VALUE,TIME_SIZE);
    instances.ticks_per_seconds=ticks_per_seconds;  //Guardo el valor de los ticks por segundo
    instances.ticks_count=START_VALUE;              //contador de ticks inicializo a cero   
    return &instances;
}

bool ClockGetTime(clock_t clock,uint8_t * time,uint8_t size){
    //memset(time,START_VALUE,size);
    memcpy(time,clock->time,size);
    return clock->valid;
}


void ClockSetupTime(clock_t clock,const uint8_t * const time,uint8_t size){
     memcpy(clock->time,time,size);
    clock->valid=true;
}


void clockNewTick(clock_t clock){
    clock->ticks_count++;
    if(clock->ticks_count==clock->ticks_per_seconds){
        clock->ticks_count=START_VALUE;
        clock->time[SECUNDS_UNIT]++;                 //si los tick lleagorn a l valor de ticks por segundo
        if(clock->time[SECUNDS_UNIT]==10){
            clock->time[SECUNDS_UNIT]=0;
            clock->time[4]++;
        } 


    }                                                
    
    


}