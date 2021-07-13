/**
 * \file Pwm.c
 * \brief source file manages the pwm functions and set up
 *
 *  Created on: 10 giu 2021
 *      Author: SMUOIO
 */
#include "Util.h"
#include "Pwm.h"
#include "PwmPublic.h"

static t_pwm spwm;


t_pwm *GetPwm(void)
{
	return(&spwm);
}
static unsigned char GetPwmParam(void)
{
	return(GetPwm()->pwm_param);
}

void setpwmparam(const unsigned char* const param)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((unsigned char*)param);
	if(RESULT_SUCCEEDED(lRet))
	{
		GetPwm()->pwm_param = *param;
	}

}


void pwm(void)
{
	static uint16_t cnt = 0x0U;
	if(GetPwmParam()>0)
	{
		if(cnt < 65535)
		{
			TIM2->CCR1 = cnt;
			cnt += 70;
		}
		else //while(CH1_DC > 0)
		{
			TIM2->CCR1 = cnt;
			cnt -= 70;
		}
	}
}
