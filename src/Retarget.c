/**
 * \file Retarget.h
 * \brief the file manages all functions used for the consolle IO
 * using the STM32 Nucleo we are using the USART 2
 */

#include "Retarget.h"
#include <stdio.h>
#include <string.h>

/**
 * \var huart2
 * variable huart assigned to the structure UART_HandleTypeDef
 */
extern UART_HandleTypeDef huart2;

e_result CheckUartState(void)
{
	e_result lret = RESULT_NOT_READY_UART;
	if(HAL_UART_GetState(&huart2) == HAL_UART_STATE_READY)
		lret = RESULT_OK;
	return(lret);
}


e_result Stm32WriteChar(uint8_t *pChar)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((uint8_t*)pChar);
	if(RESULT_SUCCEEDED(lRet))
	{
		//write single char
		//uint8_t c = (*pChar&(0x00FF));
//		if(UART_CheckIdleState(&huart2) == HAL_OK)
			HAL_UART_Transmit(&huart2, (uint8_t*)pChar, sizeof(uint8_t), 0xFF);
	}
	return(lRet);
}

e_result Stm32WriteString(uint8_t *pChar, uint32_t Size)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((uint8_t*)pChar);
	if(RESULT_SUCCEEDED(lRet))
	{
		//write single char
		//uint8_t c = (*pChar&(0x00FF));
//		if(UART_CheckIdleState(&huart2) == HAL_OK)
		{
			HAL_UART_Transmit(&huart2, (uint8_t*)pChar, Size, 0xFFFF);
			Stm32flush();
		}
	}
	return(lRet);
}

void Stm32flush(void)
{
	//__HAL_UART_FLUSH_DRREGISTER(((UART_HandleTypeDef *) huart2));
	//huart2.Instance->DR;
	memset(huart2.pTxBuffPtr,0,huart2.TxXferSize);
}



e_result Stm32ReadChar(uint8_t *pChar)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((uint8_t*)pChar);

	if(RESULT_SUCCEEDED(lRet))
	{
		//read a single chat
		uint8_t c;
		HAL_UART_Receive(&huart2, (uint8_t*)&c, 1, 0xFF);
		*pChar = c;
	}
	return(lRet);
}
static char rcvd = 0x0;
e_result Stm32ReadChar_IT(uint8_t *pChar)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((uint8_t*)pChar);

	if(RESULT_SUCCEEDED(lRet))
	{
		//read a single chat
		if (HAL_UART_Receive_IT(&huart2, (uint8_t*)&rcvd, 1) != HAL_OK)
		{
			printf("busy\n\r");
		}
		else
			*pChar = rcvd;
	}
	return(lRet);
}

