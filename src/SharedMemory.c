/**
 *\file  SharedMemory.c
 *
 *  Created on: 16 mar 2021
 *      Author: Salvatore Muoio
 */
#include <stdio.h>
#include <string.h>
#include "SharedMemory.h"
#include "OwnBus.h"
#include "Pwm.h"

/**
* \struct t_sm
* \brief the structure has the fields of all evc packet received and other
*        structure used in the application component
*/
typedef struct
{
    uint8_t core_ctrl;                 /*!< evc data control GPP->Task       */
	t_ownbus ownbus[2];
	t_pwm pwm[2];
    uint8_t iotask_is_master;          /*!< from IO Task to Application      */
	uint8_t applicationtask_is_master; /*!< from application task to io task */
}t_sm;

/**
* \var t_sm sm
* \brief static variable to the object shared memory
*/
static t_sm sm;

static t_sm *GetSm(void)
{
  return(&sm);
}

void sm_open(void)
{
  t_sm *const lSm = GetSm();
  //e_debug_request ldbgrequest = DEBUG_REQUEST_INFO;
  /* check app_id with EVC_ID*/
  if(lSm != 0)
  {
    /* reset all data in the shared relataded to evc*/
    //Debug_Request(DEBUG_REQUEST_INFO, ldbgrequest, "shared memoy init\n");
    memset(&lSm->ownbus[0], 0x0, sizeof(t_ownbus));
    memset(&lSm->pwm[0], 0x0, sizeof(t_pwm));
  }/*if*/
}

e_sm_error sm_rcvfromapplicationtask(uint32_t app_id, t_iotask * const ptriotask, uint8_t * const iotask_is_master)
{
  e_sm_error lOut = ID_KO;
  e_result lCheck = RESULT_OK;
  lCheck |= CheckArg((t_ownbus*)ptriotask);
  lCheck |= CheckArg((uint8_t*)iotask_is_master);
  /*id check static == EVC_SEND == 1*/
  if(app_id == RECV_FROM_APPLIACTION_TASK)
  {
    if(RESULT_SUCCEEDED(lCheck))
    {
      if((*iotask_is_master == 0)&(GetSm()->iotask_is_master))
      {
          /*check gpp_is_master*/
        memcpy((t_ownbus*)&ptriotask->ownbus,
              (t_ownbus*)&(GetSm()->ownbus[(GetSm()->core_ctrl+1)%2]),
              sizeof(t_ownbus));
        *iotask_is_master = GetSm()->iotask_is_master;
        GetSm()->applicationtask_is_master = 0x0U;
        lOut = SM_OK;
      }/*if*/
    }/*if*/
  }/*if*/
  return(lOut);
}

e_sm_error sm_sendtoapplicationtask(uint32_t app_id, const t_applicationtask * const ptrapptask, uint8_t application_is_master)
{
  e_sm_error lOut = ID_KO;
  e_result lCheck = RESULT_OK;
  lCheck |= CheckArg((t_applicationtask*)ptrapptask);
  /*id check static == EVC_SEND == 1*/
  if(app_id == IOTask_SEND_TO)
  {
    if(RESULT_SUCCEEDED(lCheck))
    {
      /*copy data*/
      memcpy((t_ownbus*)&(GetSm()->ownbus[GetSm()->core_ctrl]),
            (t_ownbus *)&ptrapptask->ownbus, sizeof(t_ownbus));
      /*increment the index*/
      GetSm()->core_ctrl = (GetSm()->core_ctrl+1)%2;
      GetSm()->applicationtask_is_master = application_is_master;
      lOut = SM_OK;
    }/*if*/
  }/*if*/
  return(lOut);
}

e_sm_error sm_rcvfromiotask(uint32_t app_id, t_applicationtask * const ptrapptask, uint8_t * const application_is_master)
{
	  e_sm_error lOut = ID_KO;
	  e_result lCheck = RESULT_OK;
	  lCheck |= CheckArg((t_applicationtask*)ptrapptask);
	  lCheck |= CheckArg((uint8_t*)application_is_master);
	  if(app_id == RECV_FROM_IOTASK)
	  {
	    if(RESULT_SUCCEEDED(lCheck))
	    {
	      if((*application_is_master == 0) & (GetSm()->applicationtask_is_master))
	      {
	          /*check gpp_is_master*/
	        memcpy((t_ownbus*)&ptrapptask->ownbus,
	              (t_ownbus*)&(GetSm()->ownbus[(GetSm()->core_ctrl+1)%2]),
	              sizeof(t_ownbus));
	        *application_is_master = GetSm()->applicationtask_is_master;
	        GetSm()->applicationtask_is_master = 0x0U;
	        lOut = SM_OK;
	      }/*if*/
	    }/*if*/
	  }/*if*/
	  return(lOut);
}

e_sm_error sm_sendtoiotask(uint32_t app_id, const t_iotask * const ptriotask, uint8_t iotask_is_master)
{
	e_sm_error lOut = ID_KO;
	e_result lCheck = RESULT_OK;
	lCheck |= CheckArg((t_applicationtask*)ptriotask);
	/*id check static == EVC_SEND == 1*/
	if(app_id == IOTask_SEND_TO)
	{
	  if(RESULT_SUCCEEDED(lCheck))
	  {
	    /*copy data*/
	    memcpy((t_ownbus*)&(GetSm()->ownbus[GetSm()->core_ctrl]),
	           (t_ownbus *)&ptriotask->ownbus, sizeof(t_ownbus));
	      /*increment the index*/
	    GetSm()->core_ctrl = (GetSm()->core_ctrl+1)%2;
	    GetSm()->iotask_is_master = iotask_is_master;
	    lOut = SM_OK;
	  }/*if*/
	}/*if*/
	return(lOut);
}


