/**
 * \file OwnBusPublic.h
 * \brief public interface
 *  Created on: 27 gen 2021
 *      Author: CAF_117
 */

#ifndef INCLUDE_OWNBUSPUBLIC_H_
#define INCLUDE_OWNBUSPUBLIC_H_
#include "Typedef.h"
#include "Util.h"



 /**
  * \fn uint8_t * GetDataRx(void)
  * \brief the function returns the pointer to bus structure used to rx
  * \param uinr16_t ii index of array
  * \return the pointer addressed
  */
uint8_t * GetDataRx(uint16_t ii);
/**
 * \fn void SetMaster(void)
 * \brief the function set the device as bus master
 */
 void SetMaster(void);
 /**
  * \fn e_bool IsRemoteMaster(void)
  * \brief the function set the if there's a remote master
  * \return TRUE remote master active, FALSE not active
  */
 e_bool IsRemoteMaster(void);
 /**
  * \fn void ReleaseMaster(void)
  * \brief the function reset the device as bus master
  */
 void ReleaseMaster(void);

 /**
  * \fn  e_result GetOwnBus(uint8_t * const packet);
  * \brief the function fetches the packet by physical layer
  * \param pointer to packet to send
  */
 e_result GetOwnBus(uint8_t * const packet);

 /**
  * \fn  uint8_t CheckPacketRx(void)
  * \brief the function checks if the packet is correct
  * \param return true or false
  */
uint8_t CheckPacketRx(void);
void OwnBusinit(void);
#endif /* INCLUDE_OWNBUSPUBLIC_H_ */
