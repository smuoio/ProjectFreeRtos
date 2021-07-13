/**
 *\file Config.h
 *\brief the file manages the configuration board
 *  Created on: 29 mar 2021
 *  Author: Salvatore Muoio
 */

#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_

#include "Util.h"

/**
* \struct t_busconfig
* \brief the structure manages which bus is configured
*/
typedef struct
{
	e_bool CanBus; /*!< Can Bus configured*/
	e_bool EthBus; /*!< Eth Bus configured*/
	e_bool OwnBus; /*!< Own Bus configured*/
	e_bool PWM;    /*!< PWM configured*/
}t_busconfig;


/**
* \struct t_config
* \brief the structure has the fields used to config the board
*/
typedef struct
{
	t_busconfig busconfig;
}t_config;

/**
* \fn void ConfigInit(void)
* \brief the function manages the configuration board
*/
void ConfigInit(void);
/**
* \fn t_config *GetConfig(void)
* \brief the function is the interface to configuration structure
*/
t_config *GetConfig(void);
/**
* \fn e_bool isPwmSetUp(void)
* \brief the function check if the Pwm is set up
* \return TRUE set up, FALSE otherwise
*/
e_bool isPwmSetUp(void);
/**
* \fn e_bool isOwnBusSetUp(void)
* \brief the function check if the OwnBus is set up
* \return TRUE set up, FALSE otherwise
*/
e_bool isOwnBusSetUp(void);

#endif /* INCLUDE_CONFIG_H_ */
