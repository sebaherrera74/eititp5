
#include <stdint.h>
#include "clock.h"
#include <string.h>


#define TIME_SIZE 6
#define ALARM_SIZE 4

#define START_VALUE 0
#define SECONDS_UNIT 5 //pOSICION DE LA UNIDAD DE SEGUNDOS
#define SECONDS_TENS 4 //pOSICION DE LA DECENA DE SEGUNDOS

#define MINUTS_UNIT  3 //pOSICION DE LA UNIDAD DE MINUTOS
#define MINUTS_TENS  2 //pOSICION DE LA DECENA DE MINUTOS

#define HOURS_UNIT  1 //pOSICION DE LA UNIDAD DE HORAS
#define HOURS_TENS  0 //pOSICION DE LA DECENA DE HORAS

#define MAX_VALUE_UNITS 10 //valor maximo que toman las unidades en los seg, minutosy horas
#define MAX_VALUE_TENS  6 //valor maximo que toman las decenas en los seg y minutos

#define MAX_VALUE_HOURS_UNITS  4
#define MAX_VALUE_HOURS_TENS   2

struct clock_s {
    uint8_t time[TIME_SIZE];
    uint8_t alarm[ALARM_SIZE];
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
        clock->time[SECONDS_UNIT]++;                 //si los tick llegaron a l valor de ticks por segundo
        if(clock->time[SECONDS_UNIT]==MAX_VALUE_UNITS){
            clock->time[SECONDS_UNIT]=START_VALUE;
            clock->time[SECONDS_TENS]++;

            if(clock->time[SECONDS_TENS]==MAX_VALUE_TENS){
                clock->time[SECONDS_TENS]=START_VALUE;
                clock->time[MINUTS_UNIT]++;

                if(clock->time[MINUTS_UNIT]==MAX_VALUE_UNITS){
                    clock->time[MINUTS_UNIT]=START_VALUE;
                    clock->time[MINUTS_TENS]++;
                    
                    if(clock->time[MINUTS_TENS]==MAX_VALUE_TENS){
                        clock->time[MINUTS_TENS]=START_VALUE;
                        clock->time[HOURS_UNIT]++;

                        if(clock->time[HOURS_UNIT]==MAX_VALUE_UNITS){
                        clock->time[HOURS_UNIT]=START_VALUE;
                        clock->time[HOURS_TENS]++;
                        }
                      
                        if((clock->time[HOURS_TENS]==MAX_VALUE_HOURS_TENS)
                                            &&(clock->time[HOURS_UNIT]==MAX_VALUE_HOURS_UNITS)){
                           
                                clock->time[HOURS_UNIT]=START_VALUE;
                                clock->time[HOURS_TENS]=START_VALUE;
                              
                        }          
                    }
                   
            }
        }
    } 
    }
}


void ClockSetupAlarm(clock_t clock,uint8_t const * const alarm ,uint8_t size){
    memcpy(clock->alarm,alarm,size);
}

bool ClockGetAlarm(clock_t clock,uint8_t * alarm,uint8_t size){
    memcpy(alarm,clock->alarm,size);
    return true;
}

//Si la alarma esta activa y la desactivo  