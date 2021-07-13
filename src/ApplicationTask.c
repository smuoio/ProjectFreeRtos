/**
 * \file ApplicationTask.c
 *
 *  Created on: 19 apr 2021
 *      Author: CAF_117
 */
#include "ApplicationTask.h"


static t_applicationtask sapplicationtask;

t_applicationtask *GetApplicationTask(void)
{
	return(&sapplicationtask);
}

e_result ApplicationTask(t_applicationtask * const ptask)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((t_applicationtask*)ptask);
	if(RESULT_SUCCEEDED(lRet))
	{
		//function ownbus
		// pwm function
	}
	return(lRet);
}
