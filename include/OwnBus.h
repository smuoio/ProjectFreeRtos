/**
 * \file OwnBus.h
 *
 *  Created on: 13 gen 2021
 *      Author: Salvatore Muoio
 */

#ifndef INCLUDE_OWNBUS_H_
#define INCLUDE_OWNBUS_H_
#include "Util.h"

/**
 * \enum e_bus
 * \brief the enum is used to define if the device is master or not
 */
typedef enum
{
	NO_MASTER,/*!<  No Master state */
	MASTER,   /*!<  Master state */
}e_bus;

/**
 * \struct t_buspacket
 * \brief the bus application packet
 */
typedef struct
{
	unsigned char SOF; /*!<  Start Of Frame */
	unsigned char PayLoad[2]; /*!< data */
	unsigned char EOFr; /*!<  End Of Frame */
}t_buspacket;

/**
 * \struct t_buspacketrx
 * \brief the bus application packet
 */
typedef struct
{
	unsigned char DataRx[4]; /*!<  packet rx */
}t_buspacketrx;

/**
 * \struct t_ownbus
 * \brief the bus structure used to read
 */
typedef struct
{
	e_bool is_master;          /*!<  key master logic            */
	e_bool is_remote_master;   /*!<  key remote master logic     */
	e_bool datareceived;       /*!< data received                */
	e_bool datatrasmitted;     /*!< data transmitted             */
	t_buspacket   buspacket;   /*!<  packet structure to send    */
	t_buspacketrx buspacketrx; /*!<  packet structure to receive */
}t_ownbus;

/**
 * \fn e_result WriteOwnBus(uint8_t *packet);
 * \brief the function writes the packet by physical layer
 * \param pointer to packet to send
 */
 e_result WriteOwnBus(const uint8_t * const packet);
 /**
  * \fn  t_ownbus *getOwnBusStruct(void);
  * \brief the interface function
  * \return pointer addressed to ownbus structure
  */
 t_ownbus *getOwnBusStruct(void);

 e_result ProtocolInput(unsigned char *packet);


#endif /* INCLUDE_OWNBUS_H_ */
