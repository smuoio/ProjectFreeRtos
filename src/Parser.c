/**
 * \file Parser.c
 * \brief parser configuration file
 *  Created on: 20 mag 2023
 *  \author: salvatore muoio
 */
#include "Parser.h"

const CHAR *tag[] = {"@TAG_DISPLAY", "@TAG_DISPLAY_END", "@TAG_INPUT", "@TAG_INPUT_ENDED"};

e_result parser(CHAR *buffer)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((CHAR*)buffer);
	if(RESULT_SUCCEEDED(lRet))
	{

	}
	return(lRet);

}
