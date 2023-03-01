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

#include "digital.h"
#include "chip.h"
#include "stdbool.h"

/* === Macros definitions ====================================================================== */
//Defino mas salidas
#ifndef OUTPUT_INSTANCES
        # define OUTPUT_INSTANCES 4
#endif

#ifndef INPUT_INSTANCES
        # define INPUT_INSTANCES 6
#endif


/* === Private data type declarations ========================================================== */
struct digital_output_s{
	uint8_t gpio;
	uint8_t bit;
	bool allocated;

};

struct digital_input_s{
	uint8_t gpioinput;
	uint8_t bitinput;
	bool allocatedinput;

};






/* === Private variable declarations =========================================================== */



/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

static struct digital_output_s instance[OUTPUT_INSTANCES]={0};
static struct digital_input_s instanceinput[INPUT_INSTANCES]={0};

/* === Private function implementation ========================================================= */

digital_output_t DigitalOutputAllocate(void){
	digital_output_t output=NULL;

	for (int index=0;index<OUTPUT_INSTANCES;index++){
		if (instance[index].allocated==false){
			instance[index].allocated=true;
			output=&instance[index];
			break;
		}
	}
     return output;
}

digital_input_t DigitalInputAllocate(void){
	digital_input_t input=NULL;

	for (int index=0;index<INPUT_INSTANCES;index++){
		if (instanceinput[index].allocatedinput==false){
			instanceinput[index].allocatedinput=true;
			input=&instanceinput[index];
			break;
		}
	}
     return input;
}

/* === Public function implementation ========================================================= */
digital_output_t DigitalOutputCreate(uint8_t gpio, uint8_t bit){
	digital_output_t output=DigitalOutputAllocate();

	if (output){
		output->gpio=gpio;
		output->bit=bit;
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->gpio,output->bit, false);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output->gpio,output->bit, true);
	}
	return output;
}

digital_input_t DigitalInputCreate(uint8_t gpio, uint8_t bit){
	digital_input_t input=DigitalInputAllocate();

	if (input){
		input->gpioinput=gpio;
		input->bitinput=bit;
		Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, input->gpioinput,input->bitinput,false);
	}
	return input;
}


void DigitalOutputActivate(digital_output_t output){
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->gpio, output->bit, true);
}

void DigitalOutputDeactivate(digital_output_t output){
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,output->gpio, output->bit, false);
}
void DigitalOutputToogle(digital_output_t output){
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,output->gpio,output->bit);
}

bool DigitalInputGetState(digital_input_t input){
	return (Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, input->gpioinput,input->bitinput));
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
