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

void I2C_init(void);
bool I2C_ReceiveCheck(void);

extern uint8_t ReceiveBuffer[8];
extern uint8_t SendBuffer[8];

#endif	/* I2C_H */

