/**
 * \file OwnBusMaster.c
 *
 *  Created on: 14 gen 2021
 *      Author: Salvatore Muoio
 */
#include "IOMap.h"
#include "Util.h"
#include "stm32f4xx_hal.h"
#include "OwnBus.h"
#include "OwnBusMaster.h"


e_bool IsMaster (void)
{
	return(getOwnBusStruct()->is_master);
}

void CreateStartOfFrame(void)
{
	getOwnBusStruct()->buspacket.SOF = 0x33U;
}

e_bus_error CheckStartOfFrame(const uint8_t * const pdata)
{
	const uint16_t sof = 0x33U;
	return((*pdata == sof) ? NO_ERROR_PACKET : ERROR_SOF);
}


void CreateEndOfFrame(void)
{
	getOwnBusStruct()->buspacket.EOFr = 0xFF;
}

e_bus_error CheckEndOfFrame(const uint8_t * const pdata)
{
	const uint16_t eof = 0xFF;
	return((*pdata == eof) ? NO_ERROR_PACKET : ERROR_EOF);
}

void CreatePayLoad(uint8_t *data)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((uint8_t*)data);
	if(RESULT_SUCCEEDED(lRet))
	{
		getOwnBusStruct()->buspacket.PayLoad[0] = 0xA;//*data;
		getOwnBusStruct()->buspacket.PayLoad[1] = 0x55;//*(data++);
	}
}

