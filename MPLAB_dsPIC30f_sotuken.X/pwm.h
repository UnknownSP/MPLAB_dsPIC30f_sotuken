/* 
 * File:   pwm.h
 * Author: UnknownSP
 *
 * Created on July 20, 2020, 8:39 PM
 */

#ifndef PWM_H
#define	PWM_H

#include <xc.h>
#include "p30f4012.h"
#include <libpic30.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.h"

#define MAX_DUTY 1000

typedef enum{
    FREE_MODE = 0,
    FORWARD_MODE = 1,
    BACKWARD_MODE = 2,
    BRAKE_MODE = 3,
} Drive_Mode_t;

void PWM_init(void);
void set_pwm(uint16_t duty, Drive_Mode_t mode);
void pwm_output_reset(void);

#endif	/* PWM_H */

