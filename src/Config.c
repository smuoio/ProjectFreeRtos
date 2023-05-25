/**
 * \file Config.c
 * \brief the file manages the configuration board
 *  Created on: 29 mar 2021
 *  Author: Salvatore Muoio
 */
#include <stdio.h>
#include "fatfs.h"
#include "Config.h"
#include "Parser.h"

#define CONFIG_PWM
#define CONFIG_OWNBUS
#define CONFIG_RS485

/**
* \var t_config config
* \brief static variable to the object the configuration struct
*/
static t_config config;

FATFS FatFs; 	//Fatfs handle
FIL fil; 		//File handle
FRESULT fres;
static unsigned int Cfgbytestowrite;

void ConfigInit(void)
{

	// Open the config file!!!!
	fres = f_mount(&FatFs, "", 1); //1=mount now
	HAL_Delay(1000);
	CHAR string[256];
	if (fres != FR_OK)
	{
	  	printf("f_mount error (%i)\r\n", fres);
	  	//while(1);
	}
	else
	{
	  fres = f_open(&fil, "Config.ini", FA_READ | FA_OPEN_ALWAYS);
	  if (fres != FR_OK){
		printf("f_open error -- Config File doesn't exist!!!(%i)\r\n",fres);
		// use default configuration!!!!
	  }else
	  {
	  // Parser config file
		  printf("call parser function!!!!\n\r");
		  //if(f_eof(&fil) == 0)
		  while(!f_eof(&fil))
		  {
			  f_gets(string, 256, &fil);
			  parser(string);
			  printf("Read file!!!!\n\r");
		  }
	  }
	}
	// PWM set
	printf("Config board set up\n\r");
#ifdef CONFIG_PWM
		GetConfig()->busconfig.PWM    = TRUE;
#else
		GetConfig()->busconfig.PWM    = FALSE;
#endif
#ifdef CONFIG_OWNBUS
	GetConfig()->busconfig.OwnBus = TRUE;
#else
	GetConfig()->busconfig.OwnBus = FALSE;
#endif
#ifdef CONFIG_CANBUS
	GetConfig()->busconfig.CanBus = TRUE;
#else
	GetConfig()->busconfig.CanBus = FALSE;
#endif
#ifdef TCPIP
	GetConfig()->busconfig.TCPIPBus = TRUE;
#else
	GetConfig()->busconfig.TCPIPBus = FALSE;
#endif
#ifdef CONFIG_RS485
	GetConfig()->busconfig.RS485 = TRUE;
#else
	GetConfig()->busconfig.RS485 = FALSE;
#endif
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

e_bool isCanBusSetUp(void)
{
	return(GetConfig()->busconfig.CanBus);
}
