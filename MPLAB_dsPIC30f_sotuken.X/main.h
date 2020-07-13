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

//void __attribute__((interrupt,no_auto_psv)) _SI2CInterrupt(void);

#ifdef	__cplusplus
}
#endif

#define SEND_DATA_BYTE 5
#define RECEIVE_DATA_BYTE 2

#endif	/* MAIN_H */

