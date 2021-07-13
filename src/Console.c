/*
 *\file Consolle.c
 *
 *  Created on: 14 mar 2021
 *      Author: Salvatore
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Console.h"
#include "PromptCmd.h"
#include "Retarget.h"



void Console(void)
{
	char cRxedChar = 0x0;
	static uint8_t namefun[4];
	static uint8_t ii = 0x0;
	static int val = 0x0;
	Stm32ReadChar((uint8_t*)&cRxedChar);
	//HAL_UART_Receive(&huart2, (uint8_t *) &cRxedChar, sizeof( cRxedChar ), 0xFF);
	  //echo
	  //if(cRxedChar != ' ')
	  if(ispressed(&cRxedChar) == TRUE)
	  {
	  //if (HAL_UART_GetState(&huart2) == HAL_UART_STATE_READY)
		  if(CheckUartState() == RESULT_OK)
		  {
			  if(cRxedChar == '\r')
			  {
			  //HAL_UART_Transmit(&huart2, (uint8_t *) &cRxedChar, sizeof( cRxedChar ), 0xFF );
				  Stm32WriteChar((uint8_t*)&cRxedChar);
				  cRxedChar = '\n';
				  /*check function*/
			  }
		  //HAL_UART_Transmit(&huart2, (uint8_t *) &cRxedChar, sizeof( cRxedChar ), 0xFF );
			  Stm32WriteChar((uint8_t*)&cRxedChar);
			  namefun[ii++] = cRxedChar;
			  if(ii >= 4)
			  {
				  val = atoi((char*)&namefun[3]);
			  }

		  }
	  }
	  if(cRxedChar == '\n')
	  {
		  checkfun(&namefun[0], val);
		  ii = 0x0;
		  memset(checkfun, 0, sizeof(checkfun));
	  }

}
