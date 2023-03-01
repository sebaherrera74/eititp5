/* * Copyright 2022, Sebastian Herrera <sebaherrera152@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** @file plantilla.c
 **
 ** @brief Plantilla de archivos fuente
 **
 ** Plantilla para los archivos de codigo fuente de prácticos de las 
 ** asignaturas Diseño Integrado de Sistemas Emebebidos y Sistemas Embebidos
 ** de Tiempo Real dictadas en de la Especialización en Integración de
 ** Sistemas Informaticos de la Univesidad Nacional de Tucumán
 ** 
 ** | RV | YYYY.MM.DD | Autor       | Descripción de los cambios              |
 ** |----|------------|-------------|-----------------------------------------|
 ** |  1 | 2022.10.10 | Sebastian   | Version inicial del archivo             |
 ** 
 ** @defgroup plantilla Plantilals de Archivos
 ** @brief Plantillas de archivos normalizadas
 ** @{ 
 */

/* === Inclusiones de cabeceras ============================================ */
#include "bsp.h"
#include "chip.h"
#include "poncho.h"
#include "ciaa.h"


//* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */
static struct board_s board={0};

/* === Private function declarations =========================================================== */
void DigitsInit(void);
void SegmentsInit(void);
void BuzzerInit(void);
void KeysInit(void);
void DisplayInit(void);
void WriteNumber(uint8_t segments);
void SelectDigit (uint8_t digit);
void ScreenOff(void);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */


void DigitsInit(void){
	//Configuracion de salidas en este caso los digitos
	Chip_SCU_PinMuxSet(DIGIT_1_PORT, DIGIT_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_1_FUNC);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIGIT_1_GPIO,DIGIT_1_BIT, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, DIGIT_1_GPIO,DIGIT_1_BIT, true);

	Chip_SCU_PinMuxSet(DIGIT_2_PORT, DIGIT_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_2_FUNC);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIGIT_2_GPIO,DIGIT_2_BIT, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, DIGIT_2_GPIO,DIGIT_2_BIT, true);

	Chip_SCU_PinMuxSet(DIGIT_3_PORT, DIGIT_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_3_FUNC);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIGIT_3_GPIO,DIGIT_3_BIT, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, DIGIT_3_GPIO,DIGIT_3_BIT, true);

	Chip_SCU_PinMuxSet(DIGIT_4_PORT, DIGIT_4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_4_FUNC);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,DIGIT_4_GPIO,DIGIT_4_BIT, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, DIGIT_4_GPIO,DIGIT_4_BIT, true);
}

void SegmentsInit(void){
	//Configuracion de salidas en este los segmentos de cada display
	Chip_SCU_PinMuxSet(SEGMENT_A_PORT, SEGMENT_A_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_A_FUNC);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,SEGMENT_A_GPIO,SEGMENT_A_BIT, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_A_GPIO,SEGMENT_A_BIT, true);

	Chip_SCU_PinMuxSet(SEGMENT_B_PORT, SEGMENT_B_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_B_FUNC);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,SEGMENT_B_GPIO,SEGMENT_B_BIT, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_B_GPIO,SEGMENT_B_BIT, true);

	Chip_SCU_PinMuxSet(SEGMENT_C_PORT, SEGMENT_C_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_C_FUNC);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,SEGMENT_C_GPIO,SEGMENT_C_BIT, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_C_GPIO,SEGMENT_C_BIT, true);

	Chip_SCU_PinMuxSet(SEGMENT_D_PORT, SEGMENT_D_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_D_FUNC);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,SEGMENT_D_GPIO,SEGMENT_D_BIT, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_D_GPIO,SEGMENT_D_BIT, true);

	Chip_SCU_PinMuxSet(SEGMENT_E_PORT, SEGMENT_E_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_E_FUNC);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,SEGMENT_E_GPIO,SEGMENT_E_BIT, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_E_GPIO,SEGMENT_E_BIT, true);

	Chip_SCU_PinMuxSet(SEGMENT_F_PORT, SEGMENT_F_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_F_FUNC);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,SEGMENT_F_GPIO,SEGMENT_F_BIT, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_F_GPIO,SEGMENT_F_BIT, true);

	Chip_SCU_PinMuxSet(SEGMENT_G_PORT, SEGMENT_G_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_G_FUNC);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,SEGMENT_G_GPIO,SEGMENT_G_BIT, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_G_GPIO,SEGMENT_G_BIT, true);

	Chip_SCU_PinMuxSet(SEGMENT_P_PORT, SEGMENT_P_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_P_FUNC);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,SEGMENT_P_GPIO,SEGMENT_P_BIT, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_P_GPIO,SEGMENT_P_BIT, true);
}



void BuzzerInit(void){
	//Configuracion de salidas en este caso EL BUZZER
	Chip_SCU_PinMuxSet(BUZZER_PORT, BUZZER_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | BUZZER_FUNC);
	board.buzzer=DigitalOutputCreate(BUZZER_GPIO,BUZZER_BIT);
}

void KeysInit(void){
	//Configuracion de entradas en este caso las LAS 6 TECLAS
	/******************/
	Chip_SCU_PinMuxSet(KEY_F1_PORT,KEY_F1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F1_FUNC);
	board.set_time=DigitalInputCreate(KEY_F1_GPIO,KEY_F1_BIT);

	Chip_SCU_PinMuxSet(KEY_F2_PORT,KEY_F2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F2_FUNC);
	board.set_alarm=DigitalInputCreate(KEY_F2_GPIO,KEY_F2_BIT);

	Chip_SCU_PinMuxSet(KEY_F3_PORT,KEY_F3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F3_FUNC);
	board.increment=DigitalInputCreate(KEY_F3_GPIO,KEY_F3_BIT);

	Chip_SCU_PinMuxSet(KEY_F4_PORT,KEY_F4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F4_FUNC);
	board.decrement=DigitalInputCreate(KEY_F4_GPIO,KEY_F4_BIT);

	Chip_SCU_PinMuxSet(KEY_ACCEPT_PORT,KEY_ACCEPT_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_ACCEPT_FUNC);
	board.accept=DigitalInputCreate(KEY_ACCEPT_GPIO,KEY_ACCEPT_BIT);

	Chip_SCU_PinMuxSet(KEY_CANCEL_PORT,KEY_CANCEL_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_CANCEL_FUNC);
	board.cancel=DigitalInputCreate(KEY_CANCEL_GPIO,KEY_CANCEL_BIT);

}

void DisplayInit(void){
	static const struct display_driver_s display_driver ={
				.ScreenTurnOff=ScreenOff,
				. SegmentsTurnOn=WriteNumber,
				.DigitTurnOn= SelectDigit,
		};
	board.display=DisplayCreate(4,&display_driver);
}
void WriteNumber(uint8_t segments){
	Chip_GPIO_SetValue(LPC_GPIO_PORT, SEGMENTS_GPIO,segments);
}

void SelectDigit (uint8_t digit){
	Chip_GPIO_SetValue(LPC_GPIO_PORT, DIGITS_GPIO,(1<<digit));
}

void ScreenOff(void){
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, DIGITS_GPIO,DIGITS_MASK);
	Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEGMENTS_GPIO,SEGMENTS_MASK);
}


/* === Public function implementation ========================================================= */
board_t BoardCreate(void){
	DigitsInit();
	SegmentsInit();
	BuzzerInit();
	KeysInit();
	DisplayInit();
	return &board;
}


/* === End of documentation ==================================================================== */

/** @} Final de la definición del modulo para doxygen */

