/**
 * \file IOTask.c
 *
 *  Created on: 17 mar 2021
 *      Author: Salvatore Muoio
 */
#include "IOTask.h"

static t_iotask siotask;


t_iotask *GetIoTask(void)
{
	return(&siotask);
}


e_result IOTAsk_Input(t_iotask * const ptriotask, t_applicationtask *const ptrapptask)
{
	unsigned char *lBuffer;
	e_result lRet = RESULT_OK;
	lBuffer = &GetIoTask()->ownbus.buspacketrx.DataRx[0];
	lRet = CheckArg((t_iotask*)ptriotask);
	lRet = CheckArg((t_applicationtask*)ptrapptask);
	if(RESULT_SUCCEEDED(lRet))
	{
		ProtocolInput(lBuffer);
		//pwm functiom
		pwm();
	}
	return(lRet);

}
