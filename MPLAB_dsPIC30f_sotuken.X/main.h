/* 
 * File:   main.h
 * Author: UnknownSP
 *
 * Created on July 12, 2020, 5:07 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "p30f4012.h"
#include <libpic30.h>
#include <stdlib.h>

#define SEND_DATA_BYTE 6
#define RECEIVE_DATA_BYTE 2

#define ADD_INPUT_1 PORTBbits.RB0
#define ADD_INPUT_2 PORTBbits.RB1
#define ADD_INPUT_3 PORTBbits.RB2
#define ADD_INPUT_4 PORTBbits.RB3

void init(void);

#endif	/* MAIN_H */

