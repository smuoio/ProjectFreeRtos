/**
 * \file Config.c
 * \brief the file manages the configuration board
 *  Created on: 29 mar 2021
 *  Author: Salvatore Muoio
 */
#include <stdio.h>
#include "Config.h"

/**
* \var t_config config
* \brief static variable to the object the configuration struct
*/
static t_config config;

void ConfigInit(void)
{
	// PWM set
	printf("Config board set up\n\r");
	GetConfig()->busconfig.PWM    = TRUE;
	GetConfig()->busconfig.OwnBus = TRUE;
}

t_config *GetConfig(void)
{
	return(&config);
}

e_bool isPwmSetUp(void)
{
	return(GetConfig()->busconfig.PWM);
}

e_bool isOwnBusSetUp(void)
{
	return(GetConfig()->busconfig.OwnBus);
}
