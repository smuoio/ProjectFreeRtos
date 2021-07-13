/**
 * \file Util.c
 * \brief the file manages all utility functions
 */

#include "Util.h"

typedef struct
{
	uint16_t uplimit;     /*!< high limit */
	uint16_t downlimit;   /*!< low limit */
}t_limit;

static t_limit limit;

t_limit * GetLimit(void)
{
	return(&limit);
}

e_result CheckArg(void *pArg)
{
	return((pArg != 0) ? RESULT_OK : RESULT_POINTER_NOT_ADDRESSED);
}

e_result RisingEdge(e_bool inp, e_bool * const out)
{
	e_result lRet = RESULT_OK;
	static e_bool tmp = FALSE;
	lRet |= CheckArg((e_bool*)out);
	if(RESULT_SUCCEEDED(lRet))
	{
		*out = inp&!tmp;
		tmp  = inp;
	}
	return(lRet);
}

e_result FallingEdge(e_bool inp, e_bool * const out)
{
	e_result lRet = RESULT_OK;
	static e_bool tmp = TRUE;
	lRet |= CheckArg((e_bool*)out);
	if(RESULT_SUCCEEDED(lRet))
	{
		*out = !inp&tmp;
		tmp  = inp;
	}
	return(lRet);
}

e_result ConvUint32toBool(const unsigned int inp, e_bool* const pout)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((e_bool*)pout);
	if(RESULT_SUCCEEDED(lRet))
	{
		*pout = FALSE;
		if (inp == 0x1U) *pout = TRUE ;
	}
	return(lRet);
}

e_result SetBoolean(e_bool *const inp, e_bool value)
{
	e_result lRet = RESULT_OK;
	lRet |= CheckArg((e_bool*)inp);
	if(RESULT_SUCCEEDED(lRet))
	{
		*inp = value;
	}
	return(lRet);
}

e_bool isfunctionrange(const char*const c)
{
   GetLimit()->downlimit = 48;
   GetLimit()->uplimit   = 122;
   return(((*c>= (GetLimit()->downlimit)) && (*c <= (GetLimit()->uplimit))) ? TRUE : FALSE);
}
