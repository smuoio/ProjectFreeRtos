/**
 *\file IOTask.h
 *
 *  Created on: 17 mar 2021
 *      Author: Salvatore Muoio
 */

#ifndef INCLUDE_IOTASK_H_
#define INCLUDE_IOTASK_H_
#include "Util.h"
#include "ApplicationTask.h"
#include "OwnBus.h"
#include "Pwm.h"

/**
* \struct t_iotask
* \brief structure io input in the io task
*/
typedef struct
{
	t_ownbus ownbus;
}t_iotask;

/**
* \fn t_iotask *GetIoTask(void)
* \brief function return address to structure t_iotask
* \return address
*/
t_iotask *GetIoTask(void);

/**
* \fn e_result IOTAsk_Input(t_iotask * const ptr iotask)
* \brief function manages the input in data in the task
*        the function could manage hw input, logic input
*  \param ptriotask pointer to the io task structure
*  \param ptrapptask pointer to the application task
* \return return error code
*/
e_result IOTAsk_Input(t_iotask * const ptriotask, t_applicationtask *const ptrapptask);

#endif /* INCLUDE_IOTASK_H_ */
