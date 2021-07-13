/**
 * \file Util.h
 * \brief the manages all utility functions
 */
#ifndef __UTIL_H__
#define __UTIL_H__

#include "Typedef.h"
/**
 * \fn e_result CheckArg(void *pArg)
 * \brief the function checks if the pointer is addressed
 * \param *pArg, pointer to be checked
 * \return status of check
 */
e_result CheckArg(void *pArg);
/**
 * \fn e_result RisingEdge(e_bool inp, e_bool * const out)
 * \brief the function checks the Rising Edge
 * \param inp input to check
 * \param out pointer used to result of check
 * \return status of check
 */
e_result RisingEdge(e_bool inp, e_bool * const out);
/**
 * \fn e_result FallingEdge(e_bool inp, e_bool * const out);
 * \brief the function checks the Falling Edge
 * \param inp input to check
 * \param out pointer used to result of check
 * \return status of check
 */
e_result FallingEdge(e_bool inp, e_bool * const out);
/**
 * \fn e_result ConvUint32toBool(const unsigned int inp, e_bool* const pout);
 * \brief the function converts uint 32 to boolean
 * \param inp input to check
 * \param out pointer used to result of check
 * \return status of check
 */
e_result ConvUint32toBool(const unsigned int inp, e_bool* const pout);
/**
 * \fn e_result SetBoolean(e_bool *const data, e_bool value)
 * \brief the function set a boolean variabel
 * \param *inp pointer input to set
 * \param value value to set the pointer
 * \return status of check
 */
e_result SetBoolean(e_bool *const inp, e_bool value);

e_bool isfunctionrange(const char*const c);

#endif
