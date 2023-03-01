/* Copyright 2022, Sebastian Herrera <sebaherrera152@gmail.com>
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

/** \brief Brief description of the file
 **
 ** Full file description
 **
 ** \addtogroup name Module denomination
 ** \brief Brief description of the module
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "pantalla.h"
#include  <string.h>
#include "stdbool.h"


/* === Macros definitions ====================================================================== */

#define DISPLAY_MAX_DIGITS 8
/* === Private data type declarations ========================================================== */
struct display_s{
	uint8_t digits;
	uint8_t active_digit;
	uint8_t memory[DISPLAY_MAX_DIGITS];
	struct display_driver_s driver;
};


/* === Private variable declarations =========================================================== */
static struct display_s instances[1];

static const uint8_t IMAGES[]={
		SEGMENT_A |SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_F,             //< 0
		SEGMENT_B|SEGMENT_C,                                                      //< 1
		SEGMENT_A |SEGMENT_B|SEGMENT_D|SEGMENT_E|SEGMENT_G,         	          //< 2
		SEGMENT_A |SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_G,                       //< 3
		SEGMENT_F |SEGMENT_B|SEGMENT_G|SEGMENT_C,                                 //< 4
		SEGMENT_A |SEGMENT_F|SEGMENT_G|SEGMENT_C|SEGMENT_D,                       //< 5
		SEGMENT_A |SEGMENT_F|SEGMENT_G|SEGMENT_C|SEGMENT_D|SEGMENT_E ,            //< 6
		SEGMENT_A |SEGMENT_B|SEGMENT_C,                                           //< 7
		SEGMENT_A |SEGMENT_B|SEGMENT_C|SEGMENT_D|SEGMENT_E|SEGMENT_F|SEGMENT_G ,  //< 8
		SEGMENT_A |SEGMENT_B|SEGMENT_C|SEGMENT_F|SEGMENT_G ,                      //< 9

};

/* === Private function declarations =========================================================== */



/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */
display_t DisplayCreate (uint8_t digits, display_driver_t driver){
	display_t display =instances;

	display->digits=digits;
	display->active_digit=digits-1;
	memset(display->memory,0,sizeof(display->memory));
	display->driver.ScreenTurnOff=driver->ScreenTurnOff;
	display->driver.SegmentsTurnOn=driver->SegmentsTurnOn;
	display->driver.DigitTurnOn=driver->DigitTurnOn;

	display->driver.ScreenTurnOff();
	return display;
}

void DisplayWriteBCD (display_t display,uint8_t *number ,uint8_t size){
	memset(display->memory,0,sizeof(display->memory));
	for (int index=0 ;index<size;index++){
		if(index>=display->digits) break;
		display->memory[index]=IMAGES[number[index]];
	}
}

void DisplayRefresh(display_t display){
	display->driver.ScreenTurnOff();
	if (display->active_digit==display->digits-1){
		display->active_digit=0;
	}else {

		display->active_digit=display->active_digit+1;
	}

	display->driver.SegmentsTurnOn(display->memory[display->active_digit]);
	//WriteNumber(display->memory[display->active_digit]);

	display->driver.DigitTurnOn(display->active_digit);
	//SelectDigit(display->active_digit);

}



/* === Private function implementation ========================================================= */



/* === Public function implementation ========================================================= */





/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
