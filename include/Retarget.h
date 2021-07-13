/**
 * \file Retarget.h
 * \brief the file manages all functions used for the consolle IO
 * using the STM32 Nucleo we are using the USART 2
 */

#ifndef __RETARGET_H__
#define __RETARGET_H__

#include "stm32f4xx_hal.h"
#include "Util.h"


/**
 * \fn
 * \brief function manages the write char
 */
e_result Stm32WriteChar(uint8_t *pChar);
/**
 * \fn e_result Stm32ReadChar(uint8_t *pChar);
 * \brief the function read the single char
 */
e_result Stm32ReadChar(uint8_t *pChar);
/**
 * e_result Stm32WriteString(uint8_t *pChar, uint32_t Size)
 * \brief function writes a string
 * @param pChar buffer to write
 * @param Size number to send to UART
 * @return Result ok or wrong address
 */
e_result Stm32WriteString(uint8_t *pChar, uint32_t Size);
e_result Stm32ReadChar_IT(uint8_t *pChar);
void Stm32flush(void);
e_result CheckUartState(void);



#endif
