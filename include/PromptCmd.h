/**
 * \file PromptCmd
 * \brief the file manages the prompt functions, functions used from the end user
 */

#ifndef __PROMPTCMD_H__
#define __PROMPTCMD_H__

#include "Typedef.h"

#define DATA_SIZE 3
/**
 * \struct t_TabFun
 * \brief structure manages all function configured
 */
typedef struct
{
	uint8_t cmd[DATA_SIZE];         /*!< command  */
	uint8_t param;                  /*!< param    */
	void (*pfun)(uint8_t param); /*!< pointer function addressed to the function developed  */
}t_TabFun;
/**
 * \fn void help(void)
 * \brief the help function, shows all functions developed in the board
 *
 */
void help(uint8_t param);
/**
 * \fn void status(void)
 * \brief the functions manages the staus of board
 */
void status(uint8_t param);
void reset(uint8_t param);
void bustest(uint8_t param);
void pwmtest(uint8_t param);
static void rdummy(uint8_t param){};
/**
 * \fn void PromptCmd(void)
 * \brief function manages the prompt
 */

void PromptCmd(void);
/**
 * \fn e_result getcmd(uint8_t *pCmd)
 * \brief the function get the cmd from the shell
 * \param *pCmd, command
 * \return the status of check pointer
 */
e_result getcmd(uint8_t *cmd);
/**
 * \fn e_result checkfun(uint8_t *cmd)
 * \brief function used to check which command is written in the consolle IO
 * @param cmd
 * @return the status of check
 */
e_result checkfun(uint8_t *cmd, uint8_t param);

e_bool ispressed(const char *const c);

#endif
