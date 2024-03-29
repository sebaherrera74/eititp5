#include "unity.h"
#include "clock.h"
/*
1-La librería deberá mantener la hora actual, con precisión de segundos, a partir de la 
  llamada a una función que se produce una cierta cantidad de veces por segundo.
2-La librería deberá proporcionar una función para ajustar la hora actual.
3-La librería deberá permitir la configuración, una vez al inicio, de la cantidad de 
  veces por segundo que se llamará a la función para mantener la hora actualizada.
4-La librería deberá informar que la hora actual es inválida hasta que se llama a la función
  para ajustar la hora por primera vez.
5-La librería deberá proporcionar una función para fijar la hora de la alarma.
6-La librería deberá proporcionar una función para consultar la hora fijada para la alarma.
7-La librería deberá proporcionar una función para habilitar y deshabilitar la alarma.
8-La librería deberá proporcionar una función para consultar si la alarma está, o no, habilitada.
9-La librería deberá generar un evento cuando la alarma esté habilitada y además hora 
actual coincida con la hora de la alarma.
10-La librería deberá proporcionar una función para posponer la alarma una cantidad 
   arbitraria de minutos.
11-La librería deberá manejar todas las horas como un arreglo de bytes en formato BCD 
   sin compactar, con la decena de horas en la primera posición y la unidad de los segundos
   en la última posición del vector.
*/



/* void test_inicial(void){
    TEST_FAIL_MESSAGE("Iniciamos");
}*/

#define TICKS_PER_SECOND 5
 
clock_t reloj;
bool alarm_state;

//Refactor de codigo que va repitiendo en las pruebas
void SimulateSeconds(int seconds){
  for(int index=0;index<seconds*TICKS_PER_SECOND;index++){
     clockNewTick(reloj);
  }
}

void AlarmEventHandler(clock_t clock,bool state){
  alarm_state=state;
}


void setUp(void){
 static const uint8_t INICIAL[]={1,2,3,4};
  reloj=ClockCreate(TICKS_PER_SECOND,AlarmEventHandler);
  ClockSetupTime(reloj,INICIAL,sizeof(INICIAL));
  alarm_state=false;
}

 //Configurar la libreria, consultar la hora y tiene que ser invalida
 void test_clock_start(void){
    static const uint8_t ESPERADO[]={0,0,0,0,0,0};
    uint8_t hora[6];
    uint8_t alarma[4];
    clock_t reloj=ClockCreate(TICKS_PER_SECOND,AlarmEventHandler);                 
    TEST_ASSERT_FALSE(ClockGetTime(reloj,hora,sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,sizeof(ESPERADO));
    TEST_ASSERT_FALSE(ClockGetAlarm(reloj,alarma,sizeof(alarma)));
  }

//Configurar la libreria, ajustar la hora (con valores correctos)consultar la hora y tienen
// que ser valida
void test_set_up_current_time(void){
  static const uint8_t ESPERADO[]={1,2,3,4,0,0};
  uint8_t hora[6];
  TEST_ASSERT_TRUE(ClockGetTime(reloj,hora,sizeof(hora)));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,sizeof(ESPERADO));
}

//Simular el paso de n ciclos de reloj, consultar la hora y verificar que avanzo un segundo
void test_one_second_elapsed(void){
  
  static const uint8_t ESPERADO[]={1,2,3,4,0,1}; //Hora esperada despues de un segundo
  uint8_t hora[6];
  SimulateSeconds(1);
  ClockGetTime(reloj,hora,sizeof(hora));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,sizeof(ESPERADO));
}

//Simular el paso de 10*n iclos de reloj y verificar  

void test_ten_second_elapsed(void){
  
  static const uint8_t ESPERADO[]={1,2,3,4,1,0}; //Hora esperada despues de 10 segundo seg
  uint8_t hora[6];
  SimulateSeconds(10);
  ClockGetTime(reloj,hora,sizeof(hora));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,sizeof(ESPERADO));
}

void test_one_minute_elapsed(void){
  
  static const uint8_t ESPERADO[]={1,2,3,5,0,0}; 
  uint8_t hora[6];
  SimulateSeconds(60);
  ClockGetTime(reloj,hora,sizeof(hora));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,sizeof(ESPERADO));
}

void test_ten_minute_elapsed(void){
  
  static const uint8_t ESPERADO[]={1,2,4,4,0,0}; 
  uint8_t hora[6];
  SimulateSeconds(10*60);
  ClockGetTime(reloj,hora,sizeof(hora));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,sizeof(ESPERADO));
}


void test_one_hora_elapsed(void){
  
  static const uint8_t ESPERADO[]={1,3,3,4,0,0}; 
  uint8_t hora[6];
  SimulateSeconds(60*60);
  ClockGetTime(reloj,hora,sizeof(hora));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,sizeof(ESPERADO));
}

void test_ten_hora_elapsed(void){
  
  static const uint8_t ESPERADO[]={2,2,3,4,0,0}; 
  uint8_t hora[6];
  SimulateSeconds(10*60*60);
  ClockGetTime(reloj,hora,sizeof(hora));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,sizeof(ESPERADO));
}

//Prueba de las 12 horas 
void test_twelve_hora_elapsed(void){
  static const uint8_t ESPERADO[]={0,0,3,4,0,0}; 
  uint8_t hora[6];
  SimulateSeconds(12*60*60);
  ClockGetTime(reloj,hora,sizeof(hora));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,sizeof(ESPERADO));
}
 
// 7) Configurar la hora de la alarma (con valores correctos) y revisar si la guarda.
// 9) Configurar la hora de la alarma (con valores correctos) y revisar si la queda activada.

void test_setup_and_get_alarm(void){
  static const uint8_t ALARMA[]={1,2,3,5};
  uint8_t hora[4];
  ClockSetupAlarm(reloj,ALARMA,sizeof(ALARMA));
  TEST_ASSERT_TRUE(ClockGetAlarm(reloj,hora,sizeof(hora)));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ALARMA,hora,sizeof(ALARMA));
}


//Si la alarma esta activa y la desactivo. queda desactiva , pero no cambia la hora.  

void test_setup_and_disable_alarm(void){
  static const uint8_t ALARMA[]={1,2,3,5};
  uint8_t hora[4];
  ClockSetupAlarm(reloj,ALARMA,sizeof(ALARMA));
  TEST_ASSERT_FALSE(ClockToggleAlarm(reloj));

  TEST_ASSERT_FALSE(ClockGetAlarm(reloj,hora,sizeof(hora)));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ALARMA,hora,sizeof(ALARMA));
}
// Si la alarma esta activa, y la hora del reloj coincide con la hora de 
//la alarma, entonces suena

void test_setup_and_fire_alarm(void){
  static const uint8_t ALARMA[]={1,2,3,5};
  ClockSetupAlarm(reloj,ALARMA,sizeof(ALARMA));
  SimulateSeconds(60);                         //Pasan 60 segundos y para que suene la alarma
  //Aqui compruebo si sono la alarma 
  ///TEST_ASSERT(SONO_LA_ALARMA)
  TEST_ASSERT_TRUE(alarm_state);
}