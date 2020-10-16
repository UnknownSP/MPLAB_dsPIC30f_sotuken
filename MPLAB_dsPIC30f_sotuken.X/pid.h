/* 
 * File:   pid.h
 * Author: UnknownSP
 *
 * Created on August 7, 2020, 7:57 PM
 */

#ifndef PID_H
#define	PID_H

#include <xc.h>
#include "p30f4012.h"
#include <libpic30.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.h"
#include "pwm.h"

#define MAX_PULSE_100MS 8000 //0.1*910/(0.000125*910) measured

int get_pid_duty(int16_t* operate_target, int16_t* operate_nowval, uint16_t* return_duty, Drive_Mode_t* return_mode, uint16_t target_duty, Drive_Mode_t target_mode, uint32_t time_count, int16_t encoder_count);
int get_pid_duty_2(int16_t* operate_target, int16_t* operate_nowval, uint16_t* return_duty, Drive_Mode_t* return_mode, uint16_t target_duty, Drive_Mode_t target_mode, uint32_t time_count, int16_t encoder_count);

#endif	/* PID_H */

