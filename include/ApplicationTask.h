/**
 * \file ApplicationTask.h
 *
 *  Created on: 19 apr 2021
 *      Author: CAF_117
 */

#ifndef INCLUDE_APPLICATIONTASK_H_
#define INCLUDE_APPLICATIONTASK_H_

#include "Util.h"
#include "OwnBus.h"
#include "PwmPublic.h"

/**
* \struct t_applicationtask
* \brief structure io input in the application task
*/
typedef struct
{
	t_ownbus ownbus; /*!< bus structure*/
	t_pwm    pwm;    /*!< pwm structure*/

}t_applicationtask;

/**
* \fn t_iotask *GetIoTask(void)
* \brief function return address to structure t_applicationtask
* \return address
*/
t_applicationtask *GetApplicationTask(void);

e_result ApplicationTask(t_applicationtask * const ptask);


#endif /* INCLUDE_APPLICATIONTASK_H_ */
