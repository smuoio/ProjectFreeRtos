/**
 * \file IOMap.h
 * \brief the file manages the memory IO
 *  Created on: 24 set 2020
 *      Author: CAF_117
 */

#ifndef INCLUDE_TESTIOMAP_H_
#define INCLUDE_TESTIOMAP_H_
#include "stm32f4xx_hal.h"
#include "Typedef.h"

// define the local variable used to set the IO


/**
 * \fn void TestIOMap_init(void)
 * \brief the function have to initialize the IO used in board to implement the tests
 */
//extern GPIO_InitTypeDef GPIO_TstInitStructure;

/**
 * \struct t_Gpio
 * \brief the structure is used to read the general IO used from the sw regarding the tests
 */
typedef struct
{
	uint16_t pin_0:  1; /*!<  pin 0 */
	uint16_t pin_1:  1; /*!<  pin 1 */
	uint16_t pin_2:  1; /*!<  pin 2 */
	uint16_t pin_3:  1; /*!<  pin 3 */
	uint16_t pin_4:  1; /*!<  pin 4 */
	uint16_t pin_5:  1; /*!<  pin 5 */
	uint16_t pin_6:  1; /*!<  pin 6 */
	uint16_t pin_7:  1; /*!<  pin 7 */
	uint16_t pin_8:  1; /*!<  pin 8 */
	uint16_t pin_9:  1; /*!<  pin 9 */
	uint16_t pin_10: 1; /*!<  pin 10 */
	uint16_t pin_11: 1; /*!<  pin 11 */
	uint16_t pin_12: 1; /*!<  pin 12 */
	uint16_t spare:  3; /*!<  spare */
}t_Gpio;

t_Gpio *GpioInterface(void);

/**
 * \fn void IOMap_init(void)
 * \brief the function is used to initialize the pin used for the tests
 */
void IOMap_init(void);
/**
 * \fn e_result SetIO(GPIO_TypeDef  *GPIOx, uint16_t pin2set, uint8_t value)
 * \brief the function is used to set/rest the pin
 * \param GPIOx is the address area A,B,C,D,E, F
 * \param pint2set is the specific pin (i.e GPIO_PIN_12)
 * \param value is the value TRUE or FALSE for the pin (i.e GPIO_PIN_RESET = 0,
          GPIO_PIN_SET)
 *\return ok if the pointer is addressed
 */
e_result SetIO(GPIO_TypeDef  *GPIOx, uint16_t pin2set, uint8_t value);
/**
 * \fn e_result ReadIO(GPIO_TypeDef  *GPIOx, uint16_t pin2set, GPIO_PinState *pvalue)
 * \brief the function is used to read the pin
 * \param GPIOx is the address area A,B,C,D,E, F
 * \param pint2set is the specific pin (i.e GPIO_PIN_12)
 * \param value is the value TRUE or FALSE for the pin (i.e GPIO_PIN_RESET = 0,
          GPIO_PIN_SET)
 *\return ok if the pointer is addressed
 */
e_result ReadIO(GPIO_TypeDef  *GPIOx, uint16_t pin2set, GPIO_PinState *pvalue);
/**
 * \fn e_result CheckPinStatus()
 * \brief the function is used to check the status of pin
 * \param *pvalue is the status of the specific pin (i.e GPIO_PIN_12)
 * \param pinstate is the value HiGH STATE or LOW STATE for the pin (i.e GPIO_PIN_RESET = 0,
          GPIO_PIN_SET)
 *\return ok if the pointer is addressed
 */
e_result CheckPinStatus(const GPIO_PinState *const pvalue, e_pinstate * const pinstatus);
e_result ReadAll(t_Gpio *ptrGpio);

#endif /* INCLUDE_IOMAP_H_ */
