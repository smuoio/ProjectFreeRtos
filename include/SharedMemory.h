/**
 * \file SharedMemory.h
 *
 *  Created on: 16 mar 2021
 *      Author: Salvatore Muoio
 */

#ifndef INCLUDE_RAMDUALPORT_H_
#define INCLUDE_RAMDUALPORT_H_

#include "Util.h"
#include "IoTask.h"
#include "ApplicationTask.h"


/**
* \enum e_sm_id
* \brief enumeration od ud used in functions send and receive. The ids send are
*        set only from the task that write in shared. The ids receive are set
*        only from the task that read the data in the shared.
*/
typedef enum
{
  NO_ID,                /*!< idle, not id set*/
  IOTask_SEND_TO, /*!< id used to write in the shared from io task to application task*/
  RECV_FROM_IOTASK,          /*!< id used to read in the shared the data in the application task*/
  APPLIACTION_TASK_SEND_TO,          /*!< id used to write in the shared the data from application task to io task*/
  RECV_FROM_APPLIACTION_TASK, /*!< id used to read in the shared the data in the io task */
}e_sm_id;

/**
* \enum e_sm_error
* \brief enumeration of result of functions used in the library of shared memroy
*/
typedef enum
{
  SM_OK,       /*!< return of function without error*/
  ID_KO,       /*!< return of function with error, the id is not correct*/
  NO_ID_RANGE, /*!< return of function with error, the id is not in the range*/
}e_sm_error;



/**
* \fn void sm_open(void)
* \brief function initialize the buffer of shared memory used
*/
void sm_open(void);

/**
* \fn e_sm_error sm_sendtoapplicationtask(uint32_t app_id, const t_iotask * const ptriotask, uint8_t application_is_master)
* \brief function used to write in the shared memory the field data
* \param app_id: id to be sure to manage specific data
* \param ptriotask: pointer to object STM, data already extract and stored
*                  in t_stm_data object
* \param core_is_master: variable usd to know who is the master in shared memory
* \return 0 success or number and type of error
*/
e_sm_error sm_sendtoapplicationtask(uint32_t app_id, const t_applicationtask * const ptrapptask, uint8_t application_is_master);
/**
* \fn e_sm_error sm_rcvfromapplicationtask(uint32_t app_id, t_iotask * const ptriotask, uint8_t * const iotask_is_master)
* \brief function used to read in the shared memory the applilcation data
* \param app_id: id to be sure to manage specific data
* \param ptriotask: pointer to object t_iotask, data already extract and stored
*                  in t_iotask object
* \param iotask_is_master: variable used to know who is the master in shared memory
* \return 0 success or number and type of error
*/
e_sm_error sm_rcvfromapplicationtask(uint32_t app_id, t_iotask * const ptriotask, uint8_t * const iotask_is_master);
e_sm_error sm_rcvfromiotask(uint32_t app_id, t_applicationtask * const ptrapptask, uint8_t * const application_is_master);
e_sm_error sm_sendtoiotask(uint32_t app_id, const t_iotask * const ptriotask, uint8_t iotask_is_master);

#endif /* INCLUDE_RAMDUALPORT_H_ */
