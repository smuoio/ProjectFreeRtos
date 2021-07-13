/**
 * \file PromptCmd_impl.c
 * \brief the file manages all methods described in the consolle
 */
#include <stdio.h>
#include <string.h>
#include "Retarget.h"
#include "PromptCmd.h"
#include "IOMap.h"
#include "OwnBus.h"
#include "OwnBusMaster.h"
#include "OwnBusPublic.h"


#define MASTER_TX


void help(uint8_t param)
{
	char *msg = "\t *******help function******* \n\r";
	int len = strlen(msg);
	//HAL_UART_Receive(&huart2, (char*)msg, 8, 0xFFFF);
	Stm32WriteString((uint8_t*)msg, len);
	msg = "s  status board \n\r";
	len = strlen(msg);
	Stm32WriteString((uint8_t*)msg, len);
	msg = "st  single test to run \n\r";
	len = strlen(msg);
	Stm32WriteString((uint8_t*)msg, len);
	msg = "r  reset     \n\r";
	len = strlen(msg);
	Stm32WriteString((uint8_t*)msg, len);
	msg = "bt bus test \n\r";
	len = strlen(msg);
	Stm32WriteString((uint8_t*)msg, len);
	msg = "pwm test \n\r";
	len = strlen(msg);
	Stm32WriteString((uint8_t*)msg, len);

	msg = "\t *******help function******* \n\r";
	len = strlen(msg);
	//HAL_UART_Receive(&huart2, (char*)msg, 8, 0xFFFF);
	Stm32WriteString((uint8_t*)msg, len);
}

void status(uint8_t param)
{
	char *msg = "**** status function**** \n\r";
	int len = strlen(msg);
	Stm32WriteString((uint8_t*)msg, len);
	msg = "Board STM32F446 Nucleo-64 \n\r";
	len = strlen(msg);
	Stm32WriteString((uint8_t*)msg, len);
	// cretae the packet manually!!!
	// address = 0x02;
	// data -> 1=> high signal
	//Start comm
	/*SetIO(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_Delay(200);
	SetIO(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_Delay(20);
	SetIO(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_Delay(20);
	SetIO(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_Delay(20);
	SetIO(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_Delay(20);
	SetIO(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_Delay(20);
	SetIO(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	HAL_Delay(200);*/
	if (SetIO(GPIOA, GPIO_PIN_9, GPIO_PIN_SET) == RESULT_POINTER_NOT_ADDRESSED)
	{
		// set diag!!!
		char *msg = " !!!! error in SET IO address memory!!!! \n\r";
		int len = strlen(msg);
		Stm32WriteString((uint8_t*)msg, len);
	}
	//HAL_Delay(2000);
	//static GPIO_PinState sPinState;
	//if(ReadIO(GPIOA, GPIO_PIN_6, &sPinState) == RESULT_POINTER_NOT_ADDRESSED)
	{
		// set diag!!!
	//	char *msg = " !!!! error in READ IO address memory!!!! \n\r";
	//	int len = strlen(msg);
	//	Stm32WriteString((uint8_t*)msg, len);

	}
}
void reset(uint8_t param)
{
	char *msg = "**** reset function**** \n\r";
	int len = strlen(msg);
	Stm32WriteString((uint8_t*)msg, len);
	msg = "Reset Board STM32F446 Nucleo-64 \n\r";
	len = strlen(msg);
	Stm32WriteString((uint8_t*)msg, len);
	if (SetIO(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET) == RESULT_POINTER_NOT_ADDRESSED)
	{
		// set diag!!!
		char *msg = " !!!! error in SET IO address memory!!!! \n\r";
		int len = strlen(msg);
		Stm32WriteString((uint8_t*)msg, len);
	}
	HAL_Delay(2000);
	static GPIO_PinState sPinState;
	static e_pinstate spinstate;
	if(ReadIO(GPIOA, GPIO_PIN_6, &sPinState) == RESULT_POINTER_NOT_ADDRESSED)
	{
		// set diag!!!
		char *msg = " !!!! error in READ IO address memory!!!! \n\r";
		int len = strlen(msg);
		Stm32WriteString((uint8_t*)msg, len);
	}
	CheckPinStatus(&sPinState, &spinstate);
	printf("pin state = %X\n",spinstate);
}

void bustest(uint8_t param)
{
	static char *msg = "**** bus test function**** \n\r";
	int len = strlen(msg);
	Stm32WriteString((uint8_t*)msg, len);
#ifdef MASTER_TX
	SetMaster();
	if(IsMaster())
	{
		uint8_t lTxData[2] = {10, 0xEE};
	   //read data!!
		CreateStartOfFrame();
		WriteOwnBus(&getOwnBusStruct()->buspacket.SOF);
		CreatePayLoad(lTxData);
		WriteOwnBus(&getOwnBusStruct()->buspacket.PayLoad[0]);
		//WriteOwnBus(&getOwnBusStruct()->buspacket.PayLoad[1]);
		CreateEndOfFrame();
		WriteOwnBus(&getOwnBusStruct()->buspacket.EOFr);
		//ReleaseMaster();
		/*if(1)//(IsRemoteMaster() == TRUE)
		{
			  printf("Remote Master is active\n\r");
			  GetOwnBus(lData);
			  printf("lData = %x\n", *lData);
			  lData++;
			  GetOwnBus(lData);
			  lData++;
			  GetOwnBus(lData);
			  lData++;
			  GetOwnBus(lData);
		  }
		  else
		  {
			  e_bool fallingedge = FALSE;
			  FallingEdge(IsRemoteMaster(), &fallingedge);
			  if(fallingedge == TRUE)
			  {
				  // copy data in local structure
				  // check the data received
			  }
		}*/
			  ReleaseMaster();
		  }

#else
	{
		if(IsRemoteMaster())
		{
			uint8_t data[4];
			int ii = 0x0U;
			for(;ii < 4;ii++)
			{
				GetOwnBus(&data[ii]);
			}
			// copy data in application structure
			memcpy(&getOwnBusStruct()->buspacket, data, sizeof(data));
		}
	}
#endif
}

void pwmtest(uint8_t param)
{
	printf("pwm test \n\r");
	printf("param = %d\n\r", param);
	setpwmparam(&param);
}
