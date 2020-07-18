/* 
 * File:   qei.h
 * Author: UnknownSP
 *
 * Created on July 15, 2020, 7:15 PM
 */

#ifndef QEI_H
#define	QEI_H

#include <xc.h>
#include "p30f4012.h"
#include <libpic30.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.h"

void QEI_init(void);
void get_encoder_data(int16_t *sum, int16_t *increment);

static int16_t encoder_count_num = 0;
static int increment_num = 0;

#endif	/* QEI_H */

