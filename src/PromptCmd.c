/**
 * \file PromptCmd.c
 * \brief the file manages the prompt functions
 */
//#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <string.h>
#include "Retarget.h"
#include "PromptCmd.h"
#include "Util.h"
/**
 * \def MAXINDEXFUN
 * \brief max index function console
 */
#define MAXINDEXFUN 6
const t_TabFun TabFun[MAXINDEXFUN] = {{{'h',' ',' '},0, help}, {{'s',' ',' '},0,status}, {{'b','t',' '}, 0, bustest},{{'r',' ',' '}, 0,reset}, {{'p','w','t'},0,pwmtest}, {{'d',' ',' '},0,rdummy}};
static uint8_t checksize(const uint8_t *cmd);
void PromptCmd(void)
{
	uint8_t cmd = 0x0U;//command
	static uint8_t ii = 0x0;
	static uint8_t charfun[3];
	getcmd(&cmd);
	if(cmd == '\n')
	{
	/*check function*/
		//checkfun(&charfun[0]);
		ii = 0x0;
		memset(charfun, 0, sizeof(charfun));
	}
	else
		charfun[ii++] = cmd;
}

e_result getcmd(uint8_t *cmd)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((uint8_t*)cmd);
	if(RESULT_SUCCEEDED(lRet))
	{
		{
			Stm32ReadChar(cmd);
			if(*cmd == '\r'){
				Stm32WriteChar(cmd);/**echo*/
				*cmd = '\n';
			}
			Stm32WriteChar(cmd);
		}
	}
	return(lRet);
}

e_result checkfun(uint8_t *cmd, uint8_t param)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((uint8_t*)cmd);
	if(RESULT_SUCCEEDED(lRet))
	{
		int ii = 0x0;// for index
		// for used to check if command exist and callback the right function
		for(;ii<MAXINDEXFUN-1;ii++)
		{
			if (memcmp(cmd, TabFun[ii].cmd, checksize(TabFun[ii].cmd)) == 0)//(*cmd == (TabFun[ii].cmd))
			{
				//uint8 param = atoi);
				TabFun[ii].pfun(param);
				break;
			}
		}
	}
	return(lRet);
}

static uint8_t checksize(const uint8_t *cmd)
{
	uint8_t size  = 0x0U;
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((uint8_t*)cmd);
	if(RESULT_SUCCEEDED(lRet))
	{
		int ii = 0x0;
		for(; ii< DATA_SIZE; ii++)
		{
			if (*cmd != ' ')
			{
				cmd++;
				size++;
			}
			else
				break;
		}//for
	}//if
	return(size);
}

e_bool ispressed(const char *const c)
{
	e_result lRet = RESULT_OK;
	e_bool lpress = FALSE;
	lRet |= CheckArg((uint8_t*)c);
	if(RESULT_SUCCEEDED(lRet))
	{
		if((lpress = isfunctionrange(c)) == FALSE)
		{
			if((*c == '\n') || (*c == '\r'))
				lpress = TRUE;
		}
	}
	return(lpress);
}
