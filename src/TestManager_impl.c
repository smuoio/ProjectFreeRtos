/**
 * \file TestManager_impl.c
 * \brief the manages the private function test
 *  Created on: 14 set 2020
 *      Author: Salvatore Muoio
 */
#include <IOMap.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "Retarget.h"
//#include "Timer.h"
#include "TestManager_impl.h"
#include "OwnBusMaster.h"
#include "IOMap.h"

/**
 * TODO: implement the time sequence correct!!!
 */

static void setdata(uint8_t pin, e_bool value, uint8_t * data)
{
	if(data != 0)
	{
		*data     = pin;
		*(data++) = (value == TRUE) ? 0xFF : 0x0U;
	}// if
}

void TestCheck(void)
{
	uint8_t lData[2] = {0,0};
	//if (SetIO(GPIOA, GPIO_PIN_12, GPIO_PIN_SET) == RESULT_POINTER_NOT_ADDRESSED)
	// IO to set up are located in the B pinout
	//if (SetIO(GPIOB, GPIO_PIN_0, GPIO_PIN_SET) == RESULT_POINTER_NOT_ADDRESSED)
	{
		// set diag!!!
		char *msg = " !!!! error in SET IO address memory!!!! \n\r";
		int len = strlen(msg);
		Stm32WriteString((uint8_t*)msg, len);
	}
	setdata(0, TRUE, lData);
	// create packet
	CreateStartOfFrame();
	CreatePayLoad(lData);
	//SetIO(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); //== RESULT_POINTER_NOT_ADDRESSED)
}

void TestCheckInput(void)
{

}


void TestDummy(void)
{
	printf("Dummy \n\r");
}

void Test_10Line(void)
{
	// line 10 high(1) and all other pins are low(0)
	// create matrix
	ReadAll(GpioInterface());
	printf("Test_10Line\n\r");

}
