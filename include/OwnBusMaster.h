/**
 *\file OwnBusMaster.h
 *
 *  Created on: 14 gen 2021
 *      Author: Salvatore Muoio
 */

#ifndef INCLUDE_OWNBUSMASTER_H_
#define INCLUDE_OWNBUSMASTER_H_

/**
 * \enum e_bus_error
 * \brief the enum is used to define if the pakete received is correct or not
 */
typedef enum
{
	NO_ERROR_PACKET,  /*!<  No Error packet received */
	ERROR_SOF,        /*!<  Error Start of Frame received */
	ERROR_EOF,        /*!<  Error End of Frame received */
}e_bus_error;

 /**
  * \fn  e_bool IsMaster(void);
  * \brief the function check if the device is master of communication
  * \return true  or false
  */
 e_bool IsMaster(void);
 /**
  * \fn  void CreateStartOfFrame(void)
  * \brief the function create the SOF
    */
void CreateStartOfFrame(void);
/**
  * \fn void CreateEndOfFrame(void)
  * \brief the function create the End Of Frame
  */
void CreateEndOfFrame(void);
/**
  * \fn void CreatePayLoad(uint8_t *data)
  * \brief the function copy the application data in the paylod to send
  * \param uint8_t *data application data
  */
void CreatePayLoad(uint8_t *data);
/**
 * \e_bus_error CheckStartOfFrame(const uint8_t *const pdata)
 * \brief the function checks if the start of frame received is correct
 * \param *pdata, pointer to data to verify
 * \return error sof o no error
 */
e_bus_error CheckStartOfFrame(const uint8_t *const pdata);
/**
 * \e_bus_error CheckStartOfFrame(const uint8_t *const pdata)
 * \brief the function checks if the end of frame received is correct
 * \param *pdata, pointer to data to verify
 * \return error eof o no error
 */
e_bus_error CheckEndOfFrame(const uint8_t *const pdata);
#endif /* INCLUDE_OWNBUSMASTER_H_ */
