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

//Refactor de codigo que va repitiendo en las pruebas
void setUp(void){
 static const uint8_t INICIAL[]={1,2,3,4};
  reloj=ClockCreate(TICKS_PER_SECOND);
  ClockSetupTime(reloj,INICIAL,sizeof(INICIAL));
}

void SimulateSeconds(int seconds){
  for(int index=0;index<seconds*TICKS_PER_SECOND;index++){
     clockNewTick(reloj);
  }

}
 //Configurar la libreria, consultar la hora y tiene que ser invalida
 void test_clock_start(void){
    static const uint8_t ESPERADO[]={0,0,0,0,0,0};
    uint8_t hora[6];
    clock_t reloj=ClockCreate(TICKS_PER_SECOND);                 //Paso 5 segundos
    TEST_ASSERT_FALSE(ClockGetTime(reloj,hora,sizeof(hora)));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,sizeof(ESPERADO));
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
  //for(int index=0;index<10*TICKS_PER_SECOND;index++){
  //  clockNewTick(reloj);
  //}
  ClockGetTime(reloj,hora,sizeof(hora));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,sizeof(ESPERADO));
}

void test_one_minute_elapsed(void){
  
  static const uint8_t ESPERADO[]={1,2,3,5,0,0}; 
  uint8_t hora[6];
   SimulateSeconds(60);
  //for(int index=0;index<10*TICKS_PER_SECOND;index++){
  //  clockNewTick(reloj);
  //}
  ClockGetTime(reloj,hora,sizeof(hora));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,sizeof(ESPERADO));
}
