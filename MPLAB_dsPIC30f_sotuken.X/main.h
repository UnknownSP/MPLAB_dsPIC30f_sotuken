/* 
 * File:   main.h
 * Author: UnknownSP
 *
 * Created on July 12, 2020, 5:07 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "p30f4012.h"
#include <libpic30.h>
#include <stdlib.h>
//#include "I2C.h"

void I2C_init(void);
bool I2C_ReceiveCheck(void);
void Slave_Interrupt(void);
void __attribute__((interrupt,no_auto_psv)) _SI2CInterrupt(void);
    
uint8_t ReceiveBuffer[256] = {};
uint8_t SendBuffer[256] = {};
uint8_t *ReceiveTemp;
uint8_t *SendTemp;
bool receiveflag = false;

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

