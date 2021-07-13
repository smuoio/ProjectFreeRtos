/**
 * \file TestIOMap.c
 *
 *  Created on: 01 ott 2020
 *      Author: Salvatore Muoio
 */
#include <IOMap.h>
#include "Util.h"

static t_Gpio Gpio;

void IOMap_init(void)
{

	GPIO_InitTypeDef GPIO_TstInitStructure;

	// Configure pin in output push/pull mode
	//                              TX          Master
	GPIO_TstInitStructure.Pin   = GPIO_PIN_12|GPIO_PIN_9;
	GPIO_TstInitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_TstInitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_TstInitStructure.Pull  = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_TstInitStructure);
    /*Configure GPIO pin : PA6  read the master by Y*/
	//                        remote master  RX
	GPIO_TstInitStructure.Pin  = GPIO_PIN_6|GPIO_PIN_11;
	GPIO_TstInitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_TstInitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_TstInitStructure);

	/*
1-  PB0
2-  PB1
3-  PB4
4-  PB9
5-  PB11
6-  PB15*/
	GPIO_TstInitStructure.Pin  = GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_9|GPIO_PIN_11|GPIO_PIN_15;
	GPIO_TstInitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_TstInitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_TstInitStructure);
/*
7-  PC4
8-  PC6
9-  PC8
10- PC9
11- PC10
12- PC11
13- PC12*/
	GPIO_TstInitStructure.Pin  = GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
	GPIO_TstInitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_TstInitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_TstInitStructure);

}

t_Gpio *GpioInterface(void)
{
	return(&Gpio);
}

e_result SetIO(GPIO_TypeDef  *GPIOx, uint16_t pin2set, uint8_t value)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((GPIO_TypeDef*)GPIOx);
	if(RESULT_SUCCEEDED(lRet))
		HAL_GPIO_WritePin(GPIOx, pin2set, value);
	return(lRet);
}

e_result ReadIO(GPIO_TypeDef  *GPIOx, uint16_t pin2set, GPIO_PinState *pvalue)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((GPIO_PinState*)pvalue);
	lRet |= CheckArg((GPIO_TypeDef*)GPIOx);
	if(RESULT_SUCCEEDED(lRet))
		*pvalue = HAL_GPIO_ReadPin(GPIOx, pin2set);
	return(lRet);
}

e_result CheckPinStatus(const GPIO_PinState * const pvalue, e_pinstate * const pinstatus)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((e_pinstate*)pinstatus);
	lRet |= CheckArg((GPIO_PinState*)pvalue);
	if(RESULT_SUCCEEDED(lRet))
	{
		(*pvalue == GPIO_PIN_RESET) ? (*pinstatus = LOW_STATE) : (*pinstatus = HIGH_STATE);
	}
	return(lRet);
}

e_result ReadAll(t_Gpio *ptrGpio)
{
	/*
1-  PB0
2-  PB1
3-  PB4
4-  PB9
5-  PB11
6-  PB15*/
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((t_Gpio*)ptrGpio);
	if(RESULT_SUCCEEDED(lRet))
	{
		ptrGpio->pin_0 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
		HAL_Delay(5);
		ptrGpio->pin_1 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
		HAL_Delay(5);
		ptrGpio->pin_2 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4);
		HAL_Delay(5);
		ptrGpio->pin_3 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
		HAL_Delay(5);
		ptrGpio->pin_4 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11);
		HAL_Delay(5);
		ptrGpio->pin_5 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);
		HAL_Delay(5);
/*
		7-  PC4
		8-  PC6
		9-  PC8
		10- PC9
		11- PC10
		12- PC11
		13- PC12
*/
		ptrGpio->pin_6 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4);
		HAL_Delay(5);
		ptrGpio->pin_7 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6);
		HAL_Delay(5);
		ptrGpio->pin_8 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);
		HAL_Delay(5);
		ptrGpio->pin_9 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9);
		HAL_Delay(5);
		ptrGpio->pin_10 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10);
		HAL_Delay(5);
		ptrGpio->pin_11 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11);
		HAL_Delay(5);
		ptrGpio->pin_12 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12);
		HAL_Delay(5);
	}
	return(lRet);
}
