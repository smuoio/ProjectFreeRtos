/*
 * \file OwnBus.c
 * \brief the file manages all functions used for the bus OwnBus
 *  Created on: 13 gen 2021
 *      Author: CAF_117
 */
#include <stdio.h>
#include <IOMap.h>
#include "stm32f4xx_hal.h"
//#include "Util.h"
#include "OwnBus.h"
#include "OwnBusMaster.h"
#include "OwnBusPublic.h"

#define PIN_MASTER GPIO_PIN_11
#define MAP_HW     GPIOA

/**
 * \struct t_byte
 * \brief the byte structure as bitfield
 */
typedef struct
{
	uint8_t bit0:1;/*!<  bit 0 */
    uint8_t bit1:1;/*!<  bit 1 */
	uint8_t bit2:1;/*!<  bit 2 */
	uint8_t bit3:1;/*!<  bit 3 */
	uint8_t bit4:1;/*!<  bit 4 */
	uint8_t bit5:1;/*!<  bit 5 */
	uint8_t bit6:1;/*!<  bit 6 */
	uint8_t bit7:1;/*!<  bit 7 */
}t_byte;
/**
 * \union UPacket
 * \brief the union
 */
union UPacket
{
	t_byte byte;     /*!< byte bitfield structured */
	uint8_t upacket; /*!< logic variable */
};

/**
 * \var static t_ownbus ownbus
 * \brief variable to the structure t_ownbus
 */
static t_ownbus ownbus;
/**
 * \fn static void write(const uint8_t *const packet)
 * \brief static function put the packet by physical layer
 * \param pointer to packet to send
 */
static void write(const uint8_t *const packet);
/**
 * \fn static void read(uint8_t *const packet)
 * \brief static function get the packet by physical layer
 * \param pointer to packet to read
 */
static void read(uint8_t *const packet);

t_ownbus *getOwnBusStruct(void)
{
	return(&ownbus);
}

e_result GetOwnBus(uint8_t * const packet)
{
	e_result lRet = RESULT_OK;
	lRet = CheckArg((uint8_t*)packet);
	// if remote master is high
	// read hw 4 byte!!!
	read(packet);
	printf("packet = %X\n\r",*packet);
	return(lRet);
}

static void read(uint8_t *const packet)
{

	uint8_t ii = 0x0U;
	static GPIO_PinState tmp = GPIO_PIN_RESET;
	for(;ii < 8; ii++)
	{
		HAL_Delay(50);
		ReadIO(GPIOA, GPIO_PIN_11, &tmp);
		//printf("tmp = %x\n\r", tmp);
		*packet |= (tmp << ii);
		//printf("*packet_ = %X\r\n",*packet);
		HAL_Delay(2);//-->1???!!!
		//printf("tmp = %x\n\r", tmp);
	}
}

e_result WriteOwnBus(const uint8_t *const packet)
{
	e_result lRet = RESULT_OK;
	lRet = CheckArg((uint8_t*)packet);
	if(RESULT_SUCCEEDED(lRet))
	{
		// if I'm master
		//write!!!
		write(packet);
	}
	// release if the pin is high!!
	// meanwhile we are resetting the mastership
	return(lRet);
}

static void write(const uint8_t *const packet)
{
	uint8_t ii = 0x0U;
	uint8_t loop_back = 0x0U;
	static GPIO_PinState tmp = GPIO_PIN_RESET;
	union UPacket u_packet;
	u_packet.upacket = *packet;
	// write physical layer!!!!
	for(;ii<8;ii++)
	{
		//write
		printf("u_packet.upacket = %X\n\r", u_packet.upacket);
		printf("u_packet.upacket.%X = %X\n\r", ii, (u_packet.upacket>>ii)&1);
		SetIO(GPIOA, GPIO_PIN_12,(u_packet.upacket >>ii)&1);
		HAL_Delay(50);
		ReadIO(GPIOA, GPIO_PIN_11, &tmp);
		loop_back |= (tmp << ii);
	}
	printf("loop_back = %x\n\r", loop_back);
	printf("------------------\n\r");
}

void SetMaster(void)
{
	// use physical layer to set the hw
	//SetIO(MAP_HW, PIN_MASTER, MASTER);
	// set logical master
	getOwnBusStruct()->is_master = TRUE;
	SetIO(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	//HAL_Delay(50);
}

void ReleaseMaster(void)
{
	getOwnBusStruct()->is_master = FALSE;
	SetIO(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
	SetIO(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);//????
}

e_bool IsRemoteMaster(void)
{
	GPIO_PinState remote_master = GPIO_PIN_RESET;
	//HAL_Delay(5);
	ReadIO(GPIOA, GPIO_PIN_6, &remote_master);
	return(getOwnBusStruct()->is_remote_master = (!getOwnBusStruct()->is_master & remote_master));
}

uint8_t * GetDataRx(uint16_t ii)
{
	return((ii <= 4) ? (&getOwnBusStruct()->buspacketrx.DataRx[ii]) :
			           (&getOwnBusStruct()->buspacketrx.DataRx[0]));
}


uint8_t CheckPacketRx(void)
{
	e_bus_error lBusError = NO_ERROR_PACKET;
	static uint8_t *lData;
	lData = GetDataRx(0);
	lBusError |= CheckStartOfFrame(lData);
	lData = GetDataRx(2);
	lBusError |= CheckEndOfFrame(lData);
	return(lBusError);

}

void OwnBusinit(void)
{
	int ii = 0;
	for(;ii <4; ii++)
	{
		getOwnBusStruct()->buspacketrx.DataRx[ii] = 0x0U;
	}
}

static e_bool IsDataReceived(void)
{
	return((getOwnBusStruct()->datareceived == TRUE) ? TRUE : FALSE);
}

 e_result ProtocolInput(unsigned char *packet)
 {

	e_result lRet = RESULT_OK;
	lRet = CheckArg((uint8_t*)packet);
	if(RESULT_SUCCEEDED(lRet))
	{
		if(IsRemoteMaster() == TRUE)
		{
			if(IsDataReceived() == TRUE)
			{
				// get data
				GetOwnBus(packet);
				packet++;
				GetOwnBus(packet);
				packet++;
				GetOwnBus(packet);
				packet++;
				GetOwnBus(packet);
				packet++;
				SetBoolean(&getOwnBusStruct()->datareceived, TRUE);
			}
		}
		else
		{
			//reset data received
			SetBoolean(&getOwnBusStruct()->datareceived, FALSE);
		}
	}
	return(lRet);
 }
