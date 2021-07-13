/*
 * PwmPublic.h
 *
 *  Created on: 07 lug 2021
 *      Author: CAF_117
 */

#ifndef INCLUDE_PWMPUBLIC_H_
#define INCLUDE_PWMPUBLIC_H_

typedef struct
{
	unsigned char  pwm_param;
	unsigned short frequency;
	unsigned short duty_cycle;
}t_pwm;

t_pwm *GetPwm(void);

void setpwmparam(const unsigned char* const param);




#endif /* INCLUDE_PWMPUBLIC_H_ */
