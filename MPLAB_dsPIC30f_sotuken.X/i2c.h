/* 
 * File:   i2c.h
 * Author: UnknownSP
 *
 * Created on July 12, 2020, 6:09 PM
 */

#ifndef I2C_H
#define	I2C_H

#include <xc.h>
#include "p30f4012.h"
#include <libpic30.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.h"

void I2C_init(uint8_t address);
bool I2C_ReceiveCheck(void);

extern uint8_t ReceiveBuffer[RECEIVE_DATA_BYTE];
extern uint8_t SendBuffer[SEND_DATA_BYTE+1];
extern uint8_t *ReceiveTemp;
extern uint8_t *SendTemp;


#endif	/* I2C_H */

