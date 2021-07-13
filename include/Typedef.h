/**
 * \file
 * \brief: the file manages all structs used in project and all abstarct data type
 */
#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__
#include <stdint-gcc.h>

/**
 * \enum e_result
 * \brief the enum is used as validity check in the methods
 */
typedef enum
{
	RESULT_OK,                     /*!< Result of check ok */
	RESULT_POINTER_NOT_ADDRESSED,  /*!< Result of pointer check ko */
	RESULT_OUT_OF_RANGE,           /*!< Result of range check ko */
	RESULT_NOT_READY_UART = 4,     /*!< Result of uart not ready */
}e_result;

/**
*\def RESULT_SUCCEEDED(X)
*\brief the macro is the result is correct
*/
#define RESULT_SUCCEEDED(X) ((X) == RESULT_OK)

/**
 * \typedef
 * \brief creation of UCHAR
 */
typedef unsigned char UCHAR;

/**
 * \enum e_bool
 * \brief the enum is used to define the boolean state
 */
typedef enum
{
	FALSE, /*!< FALSE state */
	TRUE,  /*!< TRUE state  */
}e_bool;

/**
 * \enum e_pinstate
 * \brief the enum is used to define the pin state
 */
typedef enum
{
	LOW_STATE, /*!< Pin Low state */
	HIGH_STATE, /*!< Pin High state */
}e_pinstate;

#endif
