/* 
 * File:   timer.h
 * Author: UnknownSP
 *
 * Created on July 18, 2020, 10:50 PM
 */

#ifndef TIMER_H
#define	TIMER_H

#include <xc.h>
#include "p30f4012.h"
#include <libpic30.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.h"

void TIMER1_init(void);
void TIMER1_START(void);
void TIMER1_STOP(void);
uint16_t get_interval_time(void);

static unsigned int timer_clock_count = 0;

#endif	/* TIMER_H */

